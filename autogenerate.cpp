//
//  autogenerate.cpp
//  cxxalsa - https://github.com/hogliux/cxxalsa
//
//  Created by Fabian Renn-Giles, fabian@fieldingdsp.com on 18th September 2022.
//  Copyright © 2024 Fielding DSP GmbH, All rights reserved.
//
//  Fielding DSP GmbH
//  Jägerstr. 36
//  14467 Potsdam, Germany
//
#include <clang-c/Index.h>
#include <iostream>
#include <memory>
#include <functional>
#include <cstring>
#include <sstream>
#include <alsa/asoundlib.h>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <optional>

struct TypeCxxOutput
{
    std::string storage;
    std::string header;
    std::string impl;
};

struct EnumParams
{
    std::string alsaname;
    std::string prettyname;
    std::string toalsa;
    std::string fromalsa;
    std::vector<std::string> values;
};

struct Primitive
{
    std::string alsaname;
    std::string prettyname;
    CXTypeKind underlying;
};

struct StructParams
{
    CXTranslationUnit unit;
    CXType type;
    std::string name;
    std::string alsaname;
    std::string prettyname;
};

std::string clang2str(CXString && str) {
    std::string result(clang_getCString(str));
    clang_disposeString(str);
    return result;
}

std::size_t superHackyWayToGetALSAsStructSizes(std::string const& type) {
    static auto* lib = ::dlopen("libasound.so", RTLD_NOW | RTLD_LOCAL);
    std::size_t (*sym)() = reinterpret_cast<std::size_t (*)()>(dlsym(lib, (std::string("snd_pcm_") + type + std::string("_sizeof")).c_str()));
    if (sym == nullptr)
        return 0;

    return (*sym)();
}

std::string capitalizeFirstLetter(std::string const& word) {
    if (word.empty()) {
        return {};
    }

    return std::string() + static_cast<char>(std::toupper(word[0])) + word.substr(1);
}

std::string underscoreNameToCamelCase(std::string const& name) {
    if (name.empty()) {
        return {};
    }

    std::vector<std::string> const words = std::invoke([&name] {
        std::istringstream ss (name);
        std::vector<std::string> result;

        for (std::string token; std::getline(ss, token, '_');) {
            if (! token.empty()) {
                result.emplace_back(std::move(token));
            }
        }

        return result;
    });

    assert(! words.empty());

    std::ostringstream ss;

    ss << words[0];

    for (std::size_t idx = 1; idx < words.size(); ++idx) {
        ss << capitalizeFirstLetter(words[idx]);
    }

    return ss.str();
}

std::string findCommonPrefix(std::vector<std::string> const& strings)
{
    if (strings.empty())
        return {};

    auto prefix = strings.front();
    for (auto it = strings.begin(); it != strings.end() && (! prefix.empty()); ++it) {
        auto const& str = *it;
        prefix = prefix.substr(0, std::min(prefix.size(), str.size()));

        while ((! prefix.empty()) && (! str.starts_with(prefix)))
            prefix = prefix.substr(0, prefix.size() - 1);
    }

    return prefix;
}

TypeCxxOutput emitAlsaStruct(CXTranslationUnit unit, CXType rootType,
                             std::string const& typeName, std::string const& prettyName, std::vector<EnumParams> const& enums,
                             std::vector<Primitive> const& primitives,
                             std::vector<StructParams> const& otherStructs) {
    auto const structSize = superHackyWayToGetALSAsStructSizes(typeName);

    if (structSize == 0)
    {
        // TODO: emit structure verbatim
        return {};
    }

    std::ostringstream storage_ss, header_ss, impl_ss;

    std::string destructor_header, destructor_impl;
    std::string copyconstructor_header, copyconstructor_impl;
    std::vector<TypeCxxOutput> methods;
    std::vector<std::string> paramNames;

    storage_ss << "struct _snd_pcm_" << typeName << " { alignas(16) std::byte _storage[" << structSize << "] = 0; };" << std::endl;

    header_ss << "class " << prettyName << " : public _snd_pcm_" << typeName << " {" << std::endl;
    
    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    auto const methodprefix = std::string("snd_pcm_") + typeName + std::string("_");

    enum class ExceptionType
    {
        none,
        negative,
        null
    };

    enum class ReturnMechanism
    {
        direct,
        reference,
        valdir
    };

    auto functionVisitor = [&] (std::string const& declname, CXType function_type, std::vector<std::string> paramNames) -> void {
        auto const first_parameter_is_this_parameter = std::invoke([&] {
            if (clang_getNumArgTypes(function_type) < 1) {
                return false;
            }

            auto first_arg_type = clang_getArgType(function_type, 0);
            if (first_arg_type.kind != CXType_Pointer) {
                return false;
            }

            auto pointee = clang_getPointeeType(first_arg_type);
            
            if (prettyName == "SWParams" || prettyName == "HWParams") {
                if (clang2str(clang_getTypeSpelling(pointee)) == "snd_pcm_t") {
                    if (clang_getNumArgTypes(function_type) < 2) {
                        return false;
                    }

                    first_arg_type = clang_getArgType(function_type, 1);
                    if (first_arg_type.kind != CXType_Pointer) {
                        return false;
                    }

                    pointee = clang_getPointeeType(first_arg_type);
                }
            }

            if (pointee.kind == CXType_Elaborated) {
                pointee = clang_Type_getNamedType(pointee);
            }

            if (pointee.kind == CXType_Typedef) {
                pointee = clang_getCanonicalType(pointee);
            }

            auto root = clang_Type_getNamedType(rootType);
            return (clang_equalTypes(pointee, root) > 0);
        });

        auto const method_name = declname.substr(methodprefix.size());
        if (method_name == "malloc") { return; }
        else if (method_name == "sizeof") { return; }
        else if (method_name == "copy") {
            {
                std::ostringstream ss;
                ss << "    " << prettyName << "(" << prettyName << " const& o" << ");";
                copyconstructor_header = ss.str();
            }
            {
                std::ostringstream ss;
                ss << prettyName << "::" << prettyName << "(" << prettyName << " const& o" << ") { snd_pcm_" << typeName << "_copy(this, &o); }";
                copyconstructor_impl = ss.str();
            }
        } else if (method_name == "free") {
            {
                std::ostringstream ss;
                ss << "    ~" << prettyName << "();";
                destructor_header = ss.str();
            }
            {
                std::ostringstream ss;
                ss << prettyName << "::~" << prettyName << "() { snd_pcm_" << prettyName << "_free(this); }";
                destructor_impl = ss.str();
            }
        } else if (first_parameter_is_this_parameter) {
            auto const isParamsSpecialCase = (prettyName == "SWParams" || prettyName == "HWParams") && clang2str(clang_getTypeSpelling(clang_getPointeeType(clang_getArgType(function_type, 0)))) == "snd_pcm_t";
            auto const isBooleanGetter = method_name.starts_with("is_") || method_name.starts_with("can_") || method_name.starts_with("supports_") || method_name == "empty" || method_name.starts_with("test");
            auto const isGetter = method_name.starts_with("get_") || isBooleanGetter;
            ExceptionType handleException = ExceptionType::none;
            ReturnMechanism returnMechanism = ReturnMechanism::direct;

            auto const camelCaseName = underscoreNameToCamelCase(std::invoke([&method_name] {
                if (! method_name.starts_with("get_")) {
                    return method_name;
                }

                return method_name.substr(std::strlen("get_"));
            }));

            auto returnType = clang_getResultType(function_type);
            std::ostringstream ss_header, ss_impl;

            auto returnTypeString = clang2str(clang_getTypeSpelling(returnType));

            std::vector<std::string> paramTypes;
            for (std::size_t i = 0; i < clang_getNumArgTypes(function_type); ++i)
            {
                paramTypes.emplace_back(clang2str(clang_getTypeSpelling(clang_getArgType(function_type, i))));
            }

            if (/*isGetter && */returnTypeString == "int") {
                handleException = ExceptionType::negative;

                if (! isGetter) {
                    returnTypeString = "void";
                }
            }

            if (returnTypeString == "const char *") {
                returnTypeString = "std::string";
            }

            EnumParams const* returnTypeEnum = nullptr;

            if (isBooleanGetter) {
                returnTypeString = "bool";
            }

            if (returnType.kind == CXType_Pointer) {
                handleException = ExceptionType::null;
            }

            auto const paramOffset = (isParamsSpecialCase ? 2 : 1);

            if (isGetter && clang_getNumArgTypes(function_type) >= (paramOffset + 1) && clang_getArgType(function_type, paramOffset).kind == CXType_Pointer)
            {
                returnMechanism = ReturnMechanism::reference;
                returnTypeString = clang2str(clang_getTypeSpelling(clang_getPointeeType(clang_getArgType(function_type, paramOffset))));

                if (paramNames[paramOffset] == "val" && clang_getNumArgTypes(function_type) >= (paramOffset + 2) && clang_getArgType(function_type, paramOffset + 1).kind == CXType_Pointer && paramNames[paramOffset + 1] == "dir") {
                    returnMechanism = ReturnMechanism::valdir;
                    returnTypeString = "ValDir";
                    paramNames.erase(paramNames.begin() + paramOffset);
                    paramTypes.erase(paramTypes.begin() + paramOffset);
                }

                paramNames.erase(paramNames.begin() + paramOffset);
                paramTypes.erase(paramTypes.begin() + paramOffset);
            }

            if (auto it = std::find_if(primitives.begin(), primitives.end(), [&] (auto const& p) { return p.alsaname == returnTypeString;}); it != primitives.end()) {
                returnTypeString = it->prettyname;
            }

            StructParams const* returnTypeStruct = nullptr;
            if (auto it = std::find_if(otherStructs.begin(), otherStructs.end(), [&] (auto const& s) { return s.alsaname == returnTypeString;}); it != otherStructs.end()) {
                returnTypeStruct = &(*it);
                returnTypeString = it->prettyname;
            }

            if (auto it = std::find_if(enums.begin(), enums.end(), [&] (auto const& e) { return e.alsaname == returnTypeString;}); it != enums.end()) {
                returnTypeEnum = &(*it);
                returnTypeString = returnTypeEnum->prettyname;
            }

            ss_header << "    " << returnTypeString << " " << camelCaseName << "(";
            for (std::size_t i = paramOffset; i < paramTypes.size(); ++i) {
                if (i > paramOffset) {
                    ss_header << ", ";
                }

                if (i < (paramTypes.size() - 1) && paramNames[i] == "val" && paramNames[i + 1] == "dir") {
                    if (paramTypes[i].contains('*')) {
                        ss_header << "ValDir& valdir";
                    } else {
                        ss_header << "ValDir const& valdir";
                    }
                    ++i;
                    continue;
                }

                auto paramType = std::invoke([&]
                {
                    if (auto it = std::find_if(enums.begin(), enums.end(), [&] (auto const& e) { return e.alsaname == paramTypes[i];}); it != enums.end()) {
                        return it->prettyname;
                    } else if (auto it = std::find_if(primitives.begin(), primitives.end(), [&] (auto const& p) { return p.alsaname == paramTypes[i];}); it != primitives.end()) {
                        return it->prettyname;
                    } else if (auto it = std::find_if(otherStructs.begin(), otherStructs.end(), [&] (auto const& s) { return s.alsaname == paramTypes[i];}); it != otherStructs.end()) {
                        return it->prettyname;
                    }

                    return paramTypes[i];
                });

                ss_header << paramType << " " << paramNames[i];
            }
            ss_header << ")" << (handleException == ExceptionType::none ? " noexcept" : "") << ";";
            ss_impl << returnTypeString << " " << prettyName << "::" << camelCaseName << "(";
            for (std::size_t i = paramOffset; i < paramTypes.size(); ++i) {
                if (i > paramOffset) {
                    ss_impl << ", ";
                }

                if (i < (paramTypes.size() - 1) && paramNames[i] == "val" && paramNames[i + 1] == "dir") {
                    if (paramTypes[i].contains('*')) {
                        ss_impl << "ValDir& a" << (i - paramOffset);
                    } else {
                        ss_impl << "ValDir const& a" << (i - paramOffset);
                    }
                    ++i;
                    continue;
                }

                auto paramType = std::invoke([&]
                {
                    if (auto it = std::find_if(enums.begin(), enums.end(), [&] (auto const& e) { return e.alsaname == paramTypes[i];}); it != enums.end()) {
                        return it->prettyname;
                    } else if (auto it = std::find_if(primitives.begin(), primitives.end(), [&] (auto const& p) { return p.alsaname == paramTypes[i];}); it != primitives.end()) {
                        return it->prettyname;
                    } else if (auto it = std::find_if(otherStructs.begin(), otherStructs.end(), [&] (auto const& s) { return s.alsaname == paramTypes[i];}); it != otherStructs.end()) {
                        return it->prettyname;
                    }

                    return paramTypes[i];
                });

                ss_impl << paramType << " a" << (i - paramOffset);
            }

            auto const exceptionWrapper = std::invoke([&] () -> std::string
            {
                if (returnTypeEnum != nullptr)
                    return "";
                
                switch (handleException)
                {
                case ExceptionType::none:     return "";
                case ExceptionType::negative: return "throwIfError(";
                case ExceptionType::null:     return "throwIfNull(";
                }

                assert(false);
                return "";
            });

            ss_impl << ")" << (handleException == ExceptionType::none ? " noexcept" : "") << " { ";

            if (returnMechanism == ReturnMechanism::reference) {
                ss_impl << (returnTypeEnum != nullptr ? returnTypeEnum->alsaname : (returnTypeStruct != nullptr ? returnTypeStruct->prettyname : returnTypeString)) << " r; ";
            } else if (returnMechanism == ReturnMechanism::valdir) {
                ss_impl << "int v, d; ";
            } else {
                ss_impl << "return ";
            }

            ss_impl << exceptionWrapper << (returnTypeEnum != nullptr ? (returnTypeEnum->fromalsa + std::string("(")) : std::string() ) << declname;
            ss_impl << "(" << (isParamsSpecialCase ? "pcm_, " : "") << "*this";

            for (std::size_t i = paramOffset; i < paramTypes.size(); ++i) {
                if (i < (paramTypes.size() - 1) && paramNames[i] == "val" && paramNames[i + 1] == "dir") {
                    if (paramTypes[i].contains('*')) {
                        ss_impl << ", &a" << (i - paramOffset) << ".value, &a" << (i - paramOffset) << ".direction";
                    } else {
                        ss_impl << ", a" << (i - paramOffset) << ".value, a" << (i - paramOffset) << ".direction";
                    }
                    ++i;
                    continue;
                }
                if (auto it = std::find_if(enums.begin(), enums.end(), [&] (auto const& e) { return e.alsaname == paramTypes[i];}); it != enums.end()) {
                    ss_impl << ", " << it->toalsa << "(a" << (i - paramOffset) << ")";
                } else {
                    ss_impl << ", a" << (i - paramOffset);
                }
            }

            if (returnMechanism == ReturnMechanism::reference) {
                ss_impl << ", &r";
            } else if (returnMechanism == ReturnMechanism::valdir) {
                ss_impl << ", &v, &d";
            }

            ss_impl << ")" << (handleException != ExceptionType::none ? ")" : "") << (returnTypeEnum != nullptr ? ")" : "");

            if (returnMechanism == ReturnMechanism::reference) {
                ss_impl << "; return " << (returnTypeEnum != nullptr ? returnTypeEnum->fromalsa + std::string("(r)") : std::string("r"));
            } else if (returnMechanism == ReturnMechanism::valdir) {
                ss_impl << "; return ValDir { .value = v, .direction = d}";
            }

            ss_impl << (isBooleanGetter ? " != 0" : "") << "; }";
            methods.emplace_back(TypeCxxOutput{.header = ss_header.str(), .impl = ss_impl.str()});
        }
    };

    struct FunctionTypeAndDeclName
    {
        CXType type;
        std::string declname;
    };

    std::optional<FunctionTypeAndDeclName> functionType;

    auto visitor = std::make_unique<std::function<CXChildVisitResult (CXCursor, CXCursor, CXClientData)>>
    ([&](CXCursor current_cursor, CXCursor parent, CXClientData client_data){
        auto source_location = clang_getCursorLocation(current_cursor);

        if (clang_Location_isFromMainFile(source_location) == 0) {
            return CXChildVisit_Recurse;
        }

        CXCursorKind cursor_kind = clang_getCursorKind(current_cursor);

        if (functionType.has_value())
        {
            if (cursor_kind != CXCursor_ParmDecl) {
                return CXChildVisit_Recurse;
            }

            paramNames.emplace_back(clang2str(clang_getCursorSpelling(current_cursor)));

            if (paramNames.size() == clang_getNumArgTypes(functionType->type)) {
                functionVisitor(functionType->declname, functionType->type, paramNames);
                paramNames.clear();
                functionType = {};
            }
        }
        else
        {
            if (cursor_kind != CXCursor_FunctionDecl) {
                return CXChildVisit_Recurse;
            }

            FunctionTypeAndDeclName ftype;

            ftype.declname = clang2str(clang_getCursorSpelling(current_cursor));

            if (! ftype.declname.starts_with(methodprefix)) {
                return CXChildVisit_Recurse;
            }

            ftype.type = clang_getCursorType(current_cursor);

            if (clang_getNumArgTypes(ftype.type) == 0) {
                functionVisitor(ftype.declname, ftype.type, {});
            } else {
                
                functionType = ftype;
            }
        }


        return CXChildVisit_Recurse;
    });

    clang_visitChildren(cursor, [](CXCursor current_cursor, CXCursor parent, CXClientData client_data){
        if (auto* _lambda = static_cast<std::function<CXChildVisitResult (CXCursor, CXCursor, CXClientData)>*>(client_data)) {
            return (*_lambda)(current_cursor, parent, client_data);
        }

        return CXChildVisit_Break;
    }, visitor.get());

    if ((! copyconstructor_impl.empty()) && (! copyconstructor_header.empty())) {
        header_ss << copyconstructor_header << std::endl;
        impl_ss << copyconstructor_impl << std::endl;
    }

    if ((! destructor_impl.empty()) && (! destructor_header.empty())) {
        header_ss << destructor_header << std::endl;
        impl_ss << destructor_impl << std::endl;
    }

    if (((! copyconstructor_impl.empty()) && (! copyconstructor_header.empty())) || ((! destructor_impl.empty()) && (! destructor_header.empty()))) {
        header_ss << std::endl;
    }

    for (auto const& method : methods) {
        header_ss << method.header << std::endl;
        impl_ss << method.impl << std::endl;
    }

    if (prettyName == "SWParams" || prettyName == "HWParams") {
        header_ss << "private:" << std::endl;
        header_ss << "    PCM* pcm_;" << std::endl;
    }

    header_ss << "};" << std::endl;

    return { .storage = storage_ss.str(), .header = header_ss.str(), .impl = impl_ss.str()};
}

int main() {
    CXIndex index = clang_createIndex(0, 0); //Create index
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        "/usr/include/alsa/pcm.h", nullptr, 0,
        nullptr, 0,
        CXTranslationUnit_None); //Parse "file.cpp"


    if (unit == nullptr){
        std::cerr << "Unable to parse translation unit. Quitting.\n";
        return 0;
    }
    CXCursor cursor = clang_getTranslationUnitCursor(unit); //Obtain a cursor at the root of the translation unit

    
    std::string currentEnum;

    std::vector<EnumParams> enums;

    std::vector<StructParams> foundRecords;
    std::vector<Primitive> primitives;

    auto policy = clang_getCursorPrintingPolicy(cursor);
    clang_PrintingPolicy_setProperty(policy, CXPrintingPolicy_FullyQualifiedName, 1);
    auto lambda = std::make_unique<std::function<CXChildVisitResult (CXCursor, CXCursor, CXClientData)>>
    ([&](CXCursor current_cursor, CXCursor parent, CXClientData client_data){
        auto source_location = clang_getCursorLocation(current_cursor);

        if (clang_Location_isFromMainFile(source_location) == 0) {
            return CXChildVisit_Recurse;
        }

        CXCursorKind cursor_kind = clang_getCursorKind(current_cursor);
        auto declname = clang2str(clang_getCursorSpelling(current_cursor));

        if (cursor_kind == CXCursor_TypedefDecl) {
            auto type = clang_getTypedefDeclUnderlyingType(current_cursor);
            if (type.kind == CXType_Elaborated) {
                auto underlying = clang_Type_getNamedType(type);

                if (underlying.kind == CXType_Record) {
                    auto recordDeclaration = clang_getTypeDeclaration(underlying);
                    if (clang_getCursorKind(recordDeclaration) == CXCursor_StructDecl) {
                        auto structname = clang2str(clang_getCursorSpelling(recordDeclaration));

                        if (declname.starts_with("snd_pcm_") && declname.ends_with("_t")) {
                            auto cononical_name =  declname.substr(std::strlen("snd_pcm_"), declname.size() - std::strlen("snd_pcm_") - std::strlen("_t"));
                            //"_snd_pcm_info"
                            if (structname == (std::string("_snd_pcm_") + cononical_name)) {
                                auto prettyname = capitalizeFirstLetter(underscoreNameToCamelCase(cononical_name));
                                if (prettyname == "HwParams") prettyname = "HWParams";
                                if (prettyname == "SwParams") prettyname = "SWParams";
                                foundRecords.emplace_back(StructParams {.unit = unit, .type = type, .name = cononical_name,
                                                                        .alsaname = declname, .prettyname = prettyname});
                                return CXChildVisit_Recurse;
                            }
                        }
                    }
                }
            }
            else if (type.kind >= CXType_FirstBuiltin && type.kind <= CXType_LastBuiltin)
            {
                auto alsaname = declname;
                auto shortname = alsaname.substr(std::strlen("snd_pcm_"));
                shortname = shortname.substr(0, shortname.size() - 2);
                auto prettyname = capitalizeFirstLetter(underscoreNameToCamelCase(shortname));
                primitives.emplace_back(Primitive {.alsaname = alsaname, .prettyname = prettyname, .underlying = type.kind});
            }
        }
        else if (cursor_kind == CXCursor_EnumDecl) {
            currentEnum.clear();

            if (declname.starts_with("_snd_") || declname.starts_with("snd_"))
                currentEnum = declname[0] == '_' ? declname.substr(1) + std::string("_t") : declname;
        }
        else if (cursor_kind == CXCursor_EnumConstantDecl && (! currentEnum.empty())) {
            EnumParams* enm;
            auto it = std::find_if(enums.begin(), enums.end(), [&] (auto const& e) { return e.alsaname == currentEnum; });
            if (it != enums.end()) {
                enm = &(*it);
            } else {
                auto shortname = currentEnum.substr(std::strlen("snd_pcm_"));
                shortname = shortname.substr(0, shortname.size() - 2);
                auto prettyName = capitalizeFirstLetter(underscoreNameToCamelCase(shortname));
                auto toalsa = underscoreNameToCamelCase(shortname) + std::string("2alsa");
                auto fromalsa = std::string("alsa2") + underscoreNameToCamelCase(shortname);
                enm = &enums.emplace_back(EnumParams {.alsaname = currentEnum, .prettyname = prettyName,  .toalsa = toalsa, .fromalsa = fromalsa, .values = std::vector<std::string>()});
            }
            
            if (std::find(enm->values.begin(), enm->values.end(), declname) == enm->values.end())
                enm->values.push_back(declname);
        }

        return CXChildVisit_Recurse;
    });

    clang_visitChildren(cursor, [](CXCursor current_cursor, CXCursor parent, CXClientData client_data){
        if (auto* _lambda = static_cast<std::function<CXChildVisitResult (CXCursor, CXCursor, CXClientData)>*>(client_data)) {
            return (*_lambda)(current_cursor, parent, client_data);
        }

        return CXChildVisit_Break;
    }, lambda.get());

    std::vector<TypeCxxOutput> cxxRecords;

    for (auto const& rcrd : foundRecords) {
        cxxRecords.emplace_back(emitAlsaStruct(rcrd.unit, rcrd.type, rcrd.name, rcrd.prettyname, enums, primitives, foundRecords));
    }

    std::ostringstream header;
    std::ostringstream impl;

    for (auto const& primitive: primitives) {
        header << "using " << primitive.prettyname << " = " << clang2str(clang_getTypeSpelling(CXType {.kind = primitive.underlying})) << ";" << std::endl;
    }

    for (auto const& rcrd : cxxRecords) {
        header << rcrd.storage << std::endl;
    }

    for (auto const& enm : enums) {
        auto shortname = enm.alsaname.substr(std::strlen("snd_pcm_"));
        header << "enum class " << enm.prettyname << " {" << std::endl;

        std::ostringstream impl2alsa;
        std::ostringstream alsa2impl;

        impl2alsa << enm.alsaname << " " << enm.toalsa << "(" << enm.prettyname << " v) noexcept {" << std::endl;
        impl2alsa << "    switch (v) {" << std::endl;

        alsa2impl << enm.prettyname << " " << enm.fromalsa << "(" << enm.alsaname << " v) noexcept {" << std::endl;
        alsa2impl << "    switch (v) {" << std::endl;

        auto const prefix = findCommonPrefix(enm.values);

        std::size_t longestValue = 0;
        for (auto const& v : enm.values) {
            std::string valueName = v;
            std::transform(valueName.begin(), valueName.end(), valueName.begin(),
                            [](unsigned char c){ return std::tolower(c); });
            valueName = underscoreNameToCamelCase(valueName.substr(prefix.size()));

            if (valueName == "last" || valueName == "private1")
                continue;
            
            longestValue = std::max(longestValue, valueName.size());
        }
        
        bool isfirst = true;
        std::optional<std::string> unknownValue;
        for (auto const& v : enm.values)
        {
            std::string valueName = v;
            std::transform(valueName.begin(), valueName.end(), valueName.begin(),
                            [](unsigned char c){ return std::tolower(c); });
            valueName = underscoreNameToCamelCase(valueName.substr(prefix.size()));
            
            if (valueName == "unknown")
                unknownValue = v;

            if (valueName == "last" || valueName == "private1")
                continue;

            impl2alsa << "    case " << enm.prettyname << "::" << valueName << ": ";
            alsa2impl << "    case " << v << ": ";

            for (std::size_t i = 0; i < (longestValue - valueName.size()); ++i) {
                impl2alsa << " ";
                alsa2impl << " ";
            }

            impl2alsa << "return " << v << ";" << std::endl;
            alsa2impl << "return " << enm.prettyname << "::" << valueName << std::endl;
            
            if (! isfirst)
            {
                header << "," << std::endl;
            }
            isfirst = false;
            header << "    " << valueName;
        }

        impl2alsa << "    default: break;" << std::endl;
        impl2alsa << "    }" << std::endl << std::endl;
        alsa2impl << "    default: break;" << std::endl;
        alsa2impl << "    }" << std::endl << std::endl;


        if (unknownValue.has_value()) {
            impl2alsa << "    return " << *unknownValue << ";" << std::endl;
            alsa2impl << "    return " << enm.prettyname << "::unknown;" << std::endl;
        } else {
            impl2alsa << "    assert(false);" << std::endl;
            impl2alsa << "    return static_cast<" << enm.alsaname << ">(-1);" << std::endl;
            alsa2impl << "    assert(false);" << std::endl;
            alsa2impl << "    return static_cast<" << enm.prettyname << ">(-1);" << std::endl;
        }
        impl2alsa << "}" << std::endl << std::endl;
        alsa2impl << "}" << std::endl << std::endl;


        header << std::endl;
        header << "};" << std::endl << std::endl;

        impl << impl2alsa.str() << std::endl << alsa2impl.str() << std::endl;
    }

    for (auto const& rcrd : cxxRecords) {
        header << rcrd.header << std::endl;
        impl << rcrd.impl << std::endl;
    }

    std::cout << header.str() << std::endl << std::endl << impl.str() << std::endl;

    clang_PrintingPolicy_dispose(policy);
    return 0;
}