//
//  cxxalsa.cpp
//  cxxalsa - https://github.com/hogliux/cxxalsa
//
//  Created by Fabian Renn-Giles, fabian@fieldingdsp.com on 18th September 2022.
//  Copyright © 2024 Fielding DSP GmbH, All rights reserved.
//
//  Fielding DSP GmbH
//  Jägerstr. 36
//  14467 Potsdam, Germany
//

//===========================================================
// This cpp file was auto generated from ALSA's C API with
// the tool created from autogenerate.cpp in the cxxalsa
// repo
//===========================================================

#include "alsacxx.hpp"
#include <cassert>
#include <cstring>
#include <functional>
#include <system_error>
#include <alsa/asoundlib.h>

using namespace alsa::pcm;

namespace
{

[[maybe_unused]] snd_pcm_class_t class2alsa(Class v) noexcept {
    switch (v) {
    case Class::generic:   return SND_PCM_CLASS_GENERIC;
    case Class::multi:     return SND_PCM_CLASS_MULTI;
    case Class::modem:     return SND_PCM_CLASS_MODEM;
    case Class::digitizer: return SND_PCM_CLASS_DIGITIZER;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_class_t>(-1);
}


[[maybe_unused]] Class alsa2class(snd_pcm_class_t v) noexcept {
    switch (v) {
    case SND_PCM_CLASS_GENERIC:   return Class::generic;
    case SND_PCM_CLASS_MULTI:     return Class::multi;
    case SND_PCM_CLASS_MODEM:     return Class::modem;
    case SND_PCM_CLASS_DIGITIZER: return Class::digitizer;
    default: break;
    }

    assert(false);
    return static_cast<Class>(-1);
}


[[maybe_unused]] snd_pcm_subclass_t subclass2alsa(Subclass v) noexcept {
    switch (v) {
    case Subclass::genericMix: return SND_PCM_SUBCLASS_GENERIC_MIX;
    case Subclass::multiMix:   return SND_PCM_SUBCLASS_MULTI_MIX;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_subclass_t>(-1);
}


[[maybe_unused]] Subclass alsa2subclass(snd_pcm_subclass_t v) noexcept {
    switch (v) {
    case SND_PCM_SUBCLASS_GENERIC_MIX: return Subclass::genericMix;
    case SND_PCM_SUBCLASS_MULTI_MIX:   return Subclass::multiMix;
    default: break;
    }

    assert(false);
    return static_cast<Subclass>(-1);
}


[[maybe_unused]] snd_pcm_stream_t stream2alsa(Stream v) noexcept {
    switch (v) {
    case Stream::playback: return SND_PCM_STREAM_PLAYBACK;
    case Stream::capture:  return SND_PCM_STREAM_CAPTURE;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_stream_t>(-1);
}


[[maybe_unused]] Stream alsa2stream(snd_pcm_stream_t v) noexcept {
    switch (v) {
    case SND_PCM_STREAM_PLAYBACK: return Stream::playback;
    case SND_PCM_STREAM_CAPTURE:  return Stream::capture;
    default: break;
    }

    assert(false);
    return static_cast<Stream>(-1);
}


[[maybe_unused]] snd_pcm_access_t access2alsa(Access v) noexcept {
    switch (v) {
    case Access::mmapInterleaved:    return SND_PCM_ACCESS_MMAP_INTERLEAVED;
    case Access::mmapNoninterleaved: return SND_PCM_ACCESS_MMAP_NONINTERLEAVED;
    case Access::mmapComplex:        return SND_PCM_ACCESS_MMAP_COMPLEX;
    case Access::rwInterleaved:      return SND_PCM_ACCESS_RW_INTERLEAVED;
    case Access::rwNoninterleaved:   return SND_PCM_ACCESS_RW_NONINTERLEAVED;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_access_t>(-1);
}


[[maybe_unused]] Access alsa2access(snd_pcm_access_t v) noexcept {
    switch (v) {
    case SND_PCM_ACCESS_MMAP_INTERLEAVED:    return Access::mmapInterleaved;
    case SND_PCM_ACCESS_MMAP_NONINTERLEAVED: return Access::mmapNoninterleaved;
    case SND_PCM_ACCESS_MMAP_COMPLEX:        return Access::mmapComplex;
    case SND_PCM_ACCESS_RW_INTERLEAVED:      return Access::rwInterleaved;
    case SND_PCM_ACCESS_RW_NONINTERLEAVED:   return Access::rwNoninterleaved;
    default: break;
    }

    assert(false);
    return static_cast<Access>(-1);
}


[[maybe_unused]] snd_pcm_format_t format2alsa(Format v) noexcept {
    switch (v) {
    case Format::unknown:          return SND_PCM_FORMAT_UNKNOWN;
    case Format::s8:               return SND_PCM_FORMAT_S8;
    case Format::u8:               return SND_PCM_FORMAT_U8;
    case Format::s16Le:            return SND_PCM_FORMAT_S16_LE;
    case Format::s16Be:            return SND_PCM_FORMAT_S16_BE;
    case Format::u16Le:            return SND_PCM_FORMAT_U16_LE;
    case Format::u16Be:            return SND_PCM_FORMAT_U16_BE;
    case Format::s24Le:            return SND_PCM_FORMAT_S24_LE;
    case Format::s24Be:            return SND_PCM_FORMAT_S24_BE;
    case Format::u24Le:            return SND_PCM_FORMAT_U24_LE;
    case Format::u24Be:            return SND_PCM_FORMAT_U24_BE;
    case Format::s32Le:            return SND_PCM_FORMAT_S32_LE;
    case Format::s32Be:            return SND_PCM_FORMAT_S32_BE;
    case Format::u32Le:            return SND_PCM_FORMAT_U32_LE;
    case Format::u32Be:            return SND_PCM_FORMAT_U32_BE;
    case Format::floatLe:          return SND_PCM_FORMAT_FLOAT_LE;
    case Format::floatBe:          return SND_PCM_FORMAT_FLOAT_BE;
    case Format::float64Le:        return SND_PCM_FORMAT_FLOAT64_LE;
    case Format::float64Be:        return SND_PCM_FORMAT_FLOAT64_BE;
    case Format::iec958SubframeLe: return SND_PCM_FORMAT_IEC958_SUBFRAME_LE;
    case Format::iec958SubframeBe: return SND_PCM_FORMAT_IEC958_SUBFRAME_BE;
    case Format::muLaw:            return SND_PCM_FORMAT_MU_LAW;
    case Format::aLaw:             return SND_PCM_FORMAT_A_LAW;
    case Format::imaAdpcm:         return SND_PCM_FORMAT_IMA_ADPCM;
    case Format::mpeg:             return SND_PCM_FORMAT_MPEG;
    case Format::gsm:              return SND_PCM_FORMAT_GSM;
    case Format::s20Le:            return SND_PCM_FORMAT_S20_LE;
    case Format::s20Be:            return SND_PCM_FORMAT_S20_BE;
    case Format::u20Le:            return SND_PCM_FORMAT_U20_LE;
    case Format::u20Be:            return SND_PCM_FORMAT_U20_BE;
    case Format::special:          return SND_PCM_FORMAT_SPECIAL;
    case Format::s243le:           return SND_PCM_FORMAT_S24_3LE;
    case Format::s243be:           return SND_PCM_FORMAT_S24_3BE;
    case Format::u243le:           return SND_PCM_FORMAT_U24_3LE;
    case Format::u243be:           return SND_PCM_FORMAT_U24_3BE;
    case Format::s203le:           return SND_PCM_FORMAT_S20_3LE;
    case Format::s203be:           return SND_PCM_FORMAT_S20_3BE;
    case Format::u203le:           return SND_PCM_FORMAT_U20_3LE;
    case Format::u203be:           return SND_PCM_FORMAT_U20_3BE;
    case Format::s183le:           return SND_PCM_FORMAT_S18_3LE;
    case Format::s183be:           return SND_PCM_FORMAT_S18_3BE;
    case Format::u183le:           return SND_PCM_FORMAT_U18_3LE;
    case Format::u183be:           return SND_PCM_FORMAT_U18_3BE;
    case Format::g72324:           return SND_PCM_FORMAT_G723_24;
    case Format::g723241b:         return SND_PCM_FORMAT_G723_24_1B;
    case Format::g72340:           return SND_PCM_FORMAT_G723_40;
    case Format::g723401b:         return SND_PCM_FORMAT_G723_40_1B;
    case Format::dsdU8:            return SND_PCM_FORMAT_DSD_U8;
    case Format::dsdU16Le:         return SND_PCM_FORMAT_DSD_U16_LE;
    case Format::dsdU32Le:         return SND_PCM_FORMAT_DSD_U32_LE;
    case Format::dsdU16Be:         return SND_PCM_FORMAT_DSD_U16_BE;
    case Format::dsdU32Be:         return SND_PCM_FORMAT_DSD_U32_BE;
    case Format::float32:          return SND_PCM_FORMAT_FLOAT;
    case Format::float64:          return SND_PCM_FORMAT_FLOAT64;
    case Format::iec958Subframe:   return SND_PCM_FORMAT_IEC958_SUBFRAME;
    case Format::s20:              return SND_PCM_FORMAT_S20;
    case Format::u20:              return SND_PCM_FORMAT_U20;
    default: break;
    }

    return SND_PCM_FORMAT_UNKNOWN;
}


[[maybe_unused]] Format alsa2format(snd_pcm_format_t v) noexcept {
    switch (v) {
    case SND_PCM_FORMAT_UNKNOWN:          return Format::unknown;
    case SND_PCM_FORMAT_S8:               return Format::s8;
    case SND_PCM_FORMAT_U8:               return Format::u8;
    case SND_PCM_FORMAT_S16_LE:            return Format::s16Le;
    case SND_PCM_FORMAT_S16_BE:            return Format::s16Be;
    case SND_PCM_FORMAT_U16_LE:            return Format::u16Le;
    case SND_PCM_FORMAT_U16_BE:            return Format::u16Be;
    case SND_PCM_FORMAT_S24_LE:            return Format::s24Le;
    case SND_PCM_FORMAT_S24_BE:            return Format::s24Be;
    case SND_PCM_FORMAT_U24_LE:            return Format::u24Le;
    case SND_PCM_FORMAT_U24_BE:            return Format::u24Be;
    case SND_PCM_FORMAT_S32_LE:            return Format::s32Le;
    case SND_PCM_FORMAT_S32_BE:            return Format::s32Be;
    case SND_PCM_FORMAT_U32_LE:            return Format::u32Le;
    case SND_PCM_FORMAT_U32_BE:            return Format::u32Be;
    case SND_PCM_FORMAT_FLOAT_LE:          return Format::floatLe;
    case SND_PCM_FORMAT_FLOAT_BE:          return Format::floatBe;
    case SND_PCM_FORMAT_FLOAT64_LE:        return Format::float64Le;
    case SND_PCM_FORMAT_FLOAT64_BE:        return Format::float64Be;
    case SND_PCM_FORMAT_IEC958_SUBFRAME_LE: return Format::iec958SubframeLe;
    case SND_PCM_FORMAT_IEC958_SUBFRAME_BE: return Format::iec958SubframeBe;
    case SND_PCM_FORMAT_MU_LAW:            return Format::muLaw;
    case SND_PCM_FORMAT_A_LAW:             return Format::aLaw;
    case SND_PCM_FORMAT_IMA_ADPCM:         return Format::imaAdpcm;
    case SND_PCM_FORMAT_MPEG:             return Format::mpeg;
    case SND_PCM_FORMAT_GSM:              return Format::gsm;
    case SND_PCM_FORMAT_S20_LE:            return Format::s20Le;
    case SND_PCM_FORMAT_S20_BE:            return Format::s20Be;
    case SND_PCM_FORMAT_U20_LE:            return Format::u20Le;
    case SND_PCM_FORMAT_U20_BE:            return Format::u20Be;
    case SND_PCM_FORMAT_SPECIAL:          return Format::special;
    case SND_PCM_FORMAT_S24_3LE:           return Format::s243le;
    case SND_PCM_FORMAT_S24_3BE:           return Format::s243be;
    case SND_PCM_FORMAT_U24_3LE:           return Format::u243le;
    case SND_PCM_FORMAT_U24_3BE:           return Format::u243be;
    case SND_PCM_FORMAT_S20_3LE:           return Format::s203le;
    case SND_PCM_FORMAT_S20_3BE:           return Format::s203be;
    case SND_PCM_FORMAT_U20_3LE:           return Format::u203le;
    case SND_PCM_FORMAT_U20_3BE:           return Format::u203be;
    case SND_PCM_FORMAT_S18_3LE:           return Format::s183le;
    case SND_PCM_FORMAT_S18_3BE:           return Format::s183be;
    case SND_PCM_FORMAT_U18_3LE:           return Format::u183le;
    case SND_PCM_FORMAT_U18_3BE:           return Format::u183be;
    case SND_PCM_FORMAT_G723_24:           return Format::g72324;
    case SND_PCM_FORMAT_G723_24_1B:         return Format::g723241b;
    case SND_PCM_FORMAT_G723_40:           return Format::g72340;
    case SND_PCM_FORMAT_G723_40_1B:         return Format::g723401b;
    case SND_PCM_FORMAT_DSD_U8:            return Format::dsdU8;
    case SND_PCM_FORMAT_DSD_U16_LE:         return Format::dsdU16Le;
    case SND_PCM_FORMAT_DSD_U32_LE:         return Format::dsdU32Le;
    case SND_PCM_FORMAT_DSD_U16_BE:         return Format::dsdU16Be;
    case SND_PCM_FORMAT_DSD_U32_BE:         return Format::dsdU32Be;
    default: break;
    }

    return Format::unknown;
}


[[maybe_unused]] snd_pcm_subformat_t subformat2alsa(Subformat v) noexcept {
    switch (v) {
    case Subformat::unknown:   return SND_PCM_SUBFORMAT_UNKNOWN;
    case Subformat::std:       return SND_PCM_SUBFORMAT_STD;
    case Subformat::msbitsMax: return SND_PCM_SUBFORMAT_MSBITS_MAX;
    case Subformat::msbits20:  return SND_PCM_SUBFORMAT_MSBITS_20;
    case Subformat::msbits24:  return SND_PCM_SUBFORMAT_MSBITS_24;
    default: break;
    }

    return SND_PCM_SUBFORMAT_UNKNOWN;
}


[[maybe_unused]] Subformat alsa2subformat(snd_pcm_subformat_t v) noexcept {
    switch (v) {
    case SND_PCM_SUBFORMAT_UNKNOWN:   return Subformat::unknown;
    case SND_PCM_SUBFORMAT_STD:       return Subformat::std;
    case SND_PCM_SUBFORMAT_MSBITS_MAX: return Subformat::msbitsMax;
    case SND_PCM_SUBFORMAT_MSBITS_20:  return Subformat::msbits20;
    case SND_PCM_SUBFORMAT_MSBITS_24:  return Subformat::msbits24;
    default: break;
    }

    return Subformat::unknown;
}


[[maybe_unused]] snd_pcm_state_t state2alsa(State v) noexcept {
    switch (v) {
    case State::open:         return SND_PCM_STATE_OPEN;
    case State::setup:        return SND_PCM_STATE_SETUP;
    case State::prepared:     return SND_PCM_STATE_PREPARED;
    case State::running:      return SND_PCM_STATE_RUNNING;
    case State::xrun:         return SND_PCM_STATE_XRUN;
    case State::draining:     return SND_PCM_STATE_DRAINING;
    case State::paused:       return SND_PCM_STATE_PAUSED;
    case State::suspended:    return SND_PCM_STATE_SUSPENDED;
    case State::disconnected: return SND_PCM_STATE_DISCONNECTED;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_state_t>(-1);
}


[[maybe_unused]] State alsa2state(snd_pcm_state_t v) noexcept {
    switch (v) {
    case SND_PCM_STATE_OPEN:         return State::open;
    case SND_PCM_STATE_SETUP:        return State::setup;
    case SND_PCM_STATE_PREPARED:     return State::prepared;
    case SND_PCM_STATE_RUNNING:      return State::running;
    case SND_PCM_STATE_XRUN:         return State::xrun;
    case SND_PCM_STATE_DRAINING:     return State::draining;
    case SND_PCM_STATE_PAUSED:       return State::paused;
    case SND_PCM_STATE_SUSPENDED:    return State::suspended;
    case SND_PCM_STATE_DISCONNECTED: return State::disconnected;
    default: break;
    }

    assert(false);
    return static_cast<State>(-1);
}


[[maybe_unused]] snd_pcm_start_t start2alsa(Start v) noexcept {
    switch (v) {
    case Start::data:       return SND_PCM_START_DATA;
    case Start::explicitly: return SND_PCM_START_EXPLICIT;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_start_t>(-1);
}


[[maybe_unused]] Start alsa2start(snd_pcm_start_t v) noexcept {
    switch (v) {
    case SND_PCM_START_DATA:     return Start::data;
    case SND_PCM_START_EXPLICIT: return Start::explicitly;
    default: break;
    }

    assert(false);
    return static_cast<Start>(-1);
}


[[maybe_unused]] snd_pcm_xrun_t xrun2alsa(Xrun v) noexcept {
    switch (v) {
    case Xrun::none: return SND_PCM_XRUN_NONE;
    case Xrun::stop: return SND_PCM_XRUN_STOP;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_xrun_t>(-1);
}


[[maybe_unused]] Xrun alsa2xrun(snd_pcm_xrun_t v) noexcept {
    switch (v) {
    case SND_PCM_XRUN_NONE: return Xrun::none;
    case SND_PCM_XRUN_STOP: return Xrun::stop;
    default: break;
    }

    assert(false);
    return static_cast<Xrun>(-1);
}


[[maybe_unused]] snd_pcm_tstamp_t tstamp2alsa(Tstamp v) noexcept {
    switch (v) {
    case Tstamp::none:   return SND_PCM_TSTAMP_NONE;
    case Tstamp::enable: return SND_PCM_TSTAMP_ENABLE;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_tstamp_t>(-1);
}


[[maybe_unused]] Tstamp alsa2tstamp(snd_pcm_tstamp_t v) noexcept {
    switch (v) {
    case SND_PCM_TSTAMP_NONE:   return Tstamp::none;
    case SND_PCM_TSTAMP_ENABLE: return Tstamp::enable;
    default: break;
    }

    assert(false);
    return static_cast<Tstamp>(-1);
}


[[maybe_unused]] snd_pcm_tstamp_type_t tstampType2alsa(TstampType v) noexcept {
    switch (v) {
    case TstampType::gettimeofday: return SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY;
    case TstampType::monotonic:    return SND_PCM_TSTAMP_TYPE_MONOTONIC;
    case TstampType::monotonicRaw: return SND_PCM_TSTAMP_TYPE_MONOTONIC_RAW;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_tstamp_type_t>(-1);
}


[[maybe_unused]] TstampType alsa2tstampType(snd_pcm_tstamp_type_t v) noexcept {
    switch (v) {
    case SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY: return TstampType::gettimeofday;
    case SND_PCM_TSTAMP_TYPE_MONOTONIC:    return TstampType::monotonic;
    case SND_PCM_TSTAMP_TYPE_MONOTONIC_RAW: return TstampType::monotonicRaw;
    default: break;
    }

    assert(false);
    return static_cast<TstampType>(-1);
}


[[maybe_unused]] snd_pcm_audio_tstamp_type_t audioTstampType2alsa(AudioTstampType v) noexcept {
    switch (v) {
    case AudioTstampType::compat:           return SND_PCM_AUDIO_TSTAMP_TYPE_COMPAT;
    case AudioTstampType::dflt:             return SND_PCM_AUDIO_TSTAMP_TYPE_DEFAULT;
    case AudioTstampType::link:             return SND_PCM_AUDIO_TSTAMP_TYPE_LINK;
    case AudioTstampType::linkAbsolute:     return SND_PCM_AUDIO_TSTAMP_TYPE_LINK_ABSOLUTE;
    case AudioTstampType::linkEstimated:    return SND_PCM_AUDIO_TSTAMP_TYPE_LINK_ESTIMATED;
    case AudioTstampType::linkSynchronized: return SND_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_audio_tstamp_type_t>(-1);
}


[[maybe_unused]] AudioTstampType alsa2audioTstampType(snd_pcm_audio_tstamp_type_t v) noexcept {
    switch (v) {
    case SND_PCM_AUDIO_TSTAMP_TYPE_COMPAT:            return AudioTstampType::compat;
    case SND_PCM_AUDIO_TSTAMP_TYPE_DEFAULT:           return AudioTstampType::dflt;
    case SND_PCM_AUDIO_TSTAMP_TYPE_LINK:              return AudioTstampType::link;
    case SND_PCM_AUDIO_TSTAMP_TYPE_LINK_ABSOLUTE:     return AudioTstampType::linkAbsolute;
    case SND_PCM_AUDIO_TSTAMP_TYPE_LINK_ESTIMATED:    return AudioTstampType::linkEstimated;
    case SND_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED: return AudioTstampType::linkSynchronized;
    default: break;
    }

    assert(false);
    return static_cast<AudioTstampType>(-1);
}


[[maybe_unused]] snd_pcm_type_t type2alsa(Type v) noexcept {
    switch (v) {
    case Type::hw:          return SND_PCM_TYPE_HW;
    case Type::hooks:       return SND_PCM_TYPE_HOOKS;
    case Type::multi:       return SND_PCM_TYPE_MULTI;
    case Type::file:        return SND_PCM_TYPE_FILE;
    case Type::null:        return SND_PCM_TYPE_NULL;
    case Type::shm:         return SND_PCM_TYPE_SHM;
    case Type::inet:        return SND_PCM_TYPE_INET;
    case Type::copy:        return SND_PCM_TYPE_COPY;
    case Type::linear:      return SND_PCM_TYPE_LINEAR;
    case Type::alaw:        return SND_PCM_TYPE_ALAW;
    case Type::mulaw:       return SND_PCM_TYPE_MULAW;
    case Type::adpcm:       return SND_PCM_TYPE_ADPCM;
    case Type::rate:        return SND_PCM_TYPE_RATE;
    case Type::route:       return SND_PCM_TYPE_ROUTE;
    case Type::plug:        return SND_PCM_TYPE_PLUG;
    case Type::share:       return SND_PCM_TYPE_SHARE;
    case Type::meter:       return SND_PCM_TYPE_METER;
    case Type::mix:         return SND_PCM_TYPE_MIX;
    case Type::droute:      return SND_PCM_TYPE_DROUTE;
    case Type::lbserver:    return SND_PCM_TYPE_LBSERVER;
    case Type::linearFloat: return SND_PCM_TYPE_LINEAR_FLOAT;
    case Type::ladspa:      return SND_PCM_TYPE_LADSPA;
    case Type::dmix:        return SND_PCM_TYPE_DMIX;
    case Type::jack:        return SND_PCM_TYPE_JACK;
    case Type::dsnoop:      return SND_PCM_TYPE_DSNOOP;
    case Type::dshare:      return SND_PCM_TYPE_DSHARE;
    case Type::iec958:      return SND_PCM_TYPE_IEC958;
    case Type::softvol:     return SND_PCM_TYPE_SOFTVOL;
    case Type::ioplug:      return SND_PCM_TYPE_IOPLUG;
    case Type::extplug:     return SND_PCM_TYPE_EXTPLUG;
    case Type::mmapEmul:    return SND_PCM_TYPE_MMAP_EMUL;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_type_t>(-1);
}


[[maybe_unused]] Type alsa2type(snd_pcm_type_t v) noexcept {
    switch (v) {
    case SND_PCM_TYPE_HW:          return Type::hw;
    case SND_PCM_TYPE_HOOKS:       return Type::hooks;
    case SND_PCM_TYPE_MULTI:       return Type::multi;
    case SND_PCM_TYPE_FILE:        return Type::file;
    case SND_PCM_TYPE_NULL:        return Type::null;
    case SND_PCM_TYPE_SHM:         return Type::shm;
    case SND_PCM_TYPE_INET:        return Type::inet;
    case SND_PCM_TYPE_COPY:        return Type::copy;
    case SND_PCM_TYPE_LINEAR:      return Type::linear;
    case SND_PCM_TYPE_ALAW:        return Type::alaw;
    case SND_PCM_TYPE_MULAW:       return Type::mulaw;
    case SND_PCM_TYPE_ADPCM:       return Type::adpcm;
    case SND_PCM_TYPE_RATE:        return Type::rate;
    case SND_PCM_TYPE_ROUTE:       return Type::route;
    case SND_PCM_TYPE_PLUG:        return Type::plug;
    case SND_PCM_TYPE_SHARE:       return Type::share;
    case SND_PCM_TYPE_METER:       return Type::meter;
    case SND_PCM_TYPE_MIX:         return Type::mix;
    case SND_PCM_TYPE_DROUTE:      return Type::droute;
    case SND_PCM_TYPE_LBSERVER:    return Type::lbserver;
    case SND_PCM_TYPE_LINEAR_FLOAT: return Type::linearFloat;
    case SND_PCM_TYPE_LADSPA:      return Type::ladspa;
    case SND_PCM_TYPE_DMIX:        return Type::dmix;
    case SND_PCM_TYPE_JACK:        return Type::jack;
    case SND_PCM_TYPE_DSNOOP:      return Type::dsnoop;
    case SND_PCM_TYPE_DSHARE:      return Type::dshare;
    case SND_PCM_TYPE_IEC958:      return Type::iec958;
    case SND_PCM_TYPE_SOFTVOL:     return Type::softvol;
    case SND_PCM_TYPE_IOPLUG:      return Type::ioplug;
    case SND_PCM_TYPE_EXTPLUG:     return Type::extplug;
    case SND_PCM_TYPE_MMAP_EMUL:    return Type::mmapEmul;
    default: break;
    }

    assert(false);
    return static_cast<Type>(-1);
}


[[maybe_unused]] snd_pcm_chmap_type chmapTy2alsa(ChmapTy v) noexcept {
    switch (v) {
    case ChmapTy::none:   return SND_CHMAP_TYPE_NONE;
    case ChmapTy::fixed:  return SND_CHMAP_TYPE_FIXED;
    case ChmapTy::var:    return SND_CHMAP_TYPE_VAR;
    case ChmapTy::paired: return SND_CHMAP_TYPE_PAIRED;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_chmap_type>(-1);
}


[[maybe_unused]] ChmapTy alsa2chmapTy(snd_pcm_chmap_type v) noexcept {
    switch (v) {
    case SND_CHMAP_TYPE_NONE:   return ChmapTy::none;
    case SND_CHMAP_TYPE_FIXED:  return ChmapTy::fixed;
    case SND_CHMAP_TYPE_VAR:    return ChmapTy::var;
    case SND_CHMAP_TYPE_PAIRED: return ChmapTy::paired;
    default: break;
    }

    assert(false);
    return static_cast<ChmapTy>(-1);
}


[[maybe_unused]] snd_pcm_chmap_position chmapPositi2alsa(ChmapPositi v) noexcept {
    switch (v) {
    case ChmapPositi::unknown: return SND_CHMAP_UNKNOWN;
    case ChmapPositi::na:      return SND_CHMAP_NA;
    case ChmapPositi::mono:    return SND_CHMAP_MONO;
    case ChmapPositi::fl:      return SND_CHMAP_FL;
    case ChmapPositi::fr:      return SND_CHMAP_FR;
    case ChmapPositi::rl:      return SND_CHMAP_RL;
    case ChmapPositi::rr:      return SND_CHMAP_RR;
    case ChmapPositi::fc:      return SND_CHMAP_FC;
    case ChmapPositi::lfe:     return SND_CHMAP_LFE;
    case ChmapPositi::sl:      return SND_CHMAP_SL;
    case ChmapPositi::sr:      return SND_CHMAP_SR;
    case ChmapPositi::rc:      return SND_CHMAP_RC;
    case ChmapPositi::flc:     return SND_CHMAP_FLC;
    case ChmapPositi::frc:     return SND_CHMAP_FRC;
    case ChmapPositi::rlc:     return SND_CHMAP_RLC;
    case ChmapPositi::rrc:     return SND_CHMAP_RRC;
    case ChmapPositi::flw:     return SND_CHMAP_FLW;
    case ChmapPositi::frw:     return SND_CHMAP_FRW;
    case ChmapPositi::flh:     return SND_CHMAP_FLH;
    case ChmapPositi::fch:     return SND_CHMAP_FCH;
    case ChmapPositi::frh:     return SND_CHMAP_FRH;
    case ChmapPositi::tc:      return SND_CHMAP_TC;
    case ChmapPositi::tfl:     return SND_CHMAP_TFL;
    case ChmapPositi::tfr:     return SND_CHMAP_TFR;
    case ChmapPositi::tfc:     return SND_CHMAP_TFC;
    case ChmapPositi::trl:     return SND_CHMAP_TRL;
    case ChmapPositi::trr:     return SND_CHMAP_TRR;
    case ChmapPositi::trc:     return SND_CHMAP_TRC;
    case ChmapPositi::tflc:    return SND_CHMAP_TFLC;
    case ChmapPositi::tfrc:    return SND_CHMAP_TFRC;
    case ChmapPositi::tsl:     return SND_CHMAP_TSL;
    case ChmapPositi::tsr:     return SND_CHMAP_TSR;
    case ChmapPositi::llfe:    return SND_CHMAP_LLFE;
    case ChmapPositi::rlfe:    return SND_CHMAP_RLFE;
    case ChmapPositi::bc:      return SND_CHMAP_BC;
    case ChmapPositi::blc:     return SND_CHMAP_BLC;
    case ChmapPositi::brc:     return SND_CHMAP_BRC;
    default: break;
    }

    return SND_CHMAP_UNKNOWN;
}


[[maybe_unused]] ChmapPositi alsa2chmapPositi(snd_pcm_chmap_position v) noexcept {
    switch (v) {
    case SND_CHMAP_UNKNOWN: return ChmapPositi::unknown;
    case SND_CHMAP_NA:      return ChmapPositi::na;
    case SND_CHMAP_MONO:    return ChmapPositi::mono;
    case SND_CHMAP_FL:      return ChmapPositi::fl;
    case SND_CHMAP_FR:      return ChmapPositi::fr;
    case SND_CHMAP_RL:      return ChmapPositi::rl;
    case SND_CHMAP_RR:      return ChmapPositi::rr;
    case SND_CHMAP_FC:      return ChmapPositi::fc;
    case SND_CHMAP_LFE:     return ChmapPositi::lfe;
    case SND_CHMAP_SL:      return ChmapPositi::sl;
    case SND_CHMAP_SR:      return ChmapPositi::sr;
    case SND_CHMAP_RC:      return ChmapPositi::rc;
    case SND_CHMAP_FLC:     return ChmapPositi::flc;
    case SND_CHMAP_FRC:     return ChmapPositi::frc;
    case SND_CHMAP_RLC:     return ChmapPositi::rlc;
    case SND_CHMAP_RRC:     return ChmapPositi::rrc;
    case SND_CHMAP_FLW:     return ChmapPositi::flw;
    case SND_CHMAP_FRW:     return ChmapPositi::frw;
    case SND_CHMAP_FLH:     return ChmapPositi::flh;
    case SND_CHMAP_FCH:     return ChmapPositi::fch;
    case SND_CHMAP_FRH:     return ChmapPositi::frh;
    case SND_CHMAP_TC:      return ChmapPositi::tc;
    case SND_CHMAP_TFL:     return ChmapPositi::tfl;
    case SND_CHMAP_TFR:     return ChmapPositi::tfr;
    case SND_CHMAP_TFC:     return ChmapPositi::tfc;
    case SND_CHMAP_TRL:     return ChmapPositi::trl;
    case SND_CHMAP_TRR:     return ChmapPositi::trr;
    case SND_CHMAP_TRC:     return ChmapPositi::trc;
    case SND_CHMAP_TFLC:    return ChmapPositi::tflc;
    case SND_CHMAP_TFRC:    return ChmapPositi::tfrc;
    case SND_CHMAP_TSL:     return ChmapPositi::tsl;
    case SND_CHMAP_TSR:     return ChmapPositi::tsr;
    case SND_CHMAP_LLFE:    return ChmapPositi::llfe;
    case SND_CHMAP_RLFE:    return ChmapPositi::rlfe;
    case SND_CHMAP_BC:      return ChmapPositi::bc;
    case SND_CHMAP_BLC:     return ChmapPositi::blc;
    case SND_CHMAP_BRC:     return ChmapPositi::brc;
    default: break;
    }

    return ChmapPositi::unknown;
}


[[maybe_unused]] snd_pcm_hook_type_t hookType2alsa(HookType v) noexcept {
    switch (v) {
    case HookType::hwParams: return SND_PCM_HOOK_TYPE_HW_PARAMS;
    case HookType::hwFree:   return SND_PCM_HOOK_TYPE_HW_FREE;
    case HookType::close:    return SND_PCM_HOOK_TYPE_CLOSE;
    default: break;
    }

    assert(false);
    return static_cast<snd_pcm_hook_type_t>(-1);
}


[[maybe_unused]] HookType alsa2hookType(snd_pcm_hook_type_t v) noexcept {
    switch (v) {
    case SND_PCM_HOOK_TYPE_HW_PARAMS: return HookType::hwParams;
    case SND_PCM_HOOK_TYPE_HW_FREE:   return HookType::hwFree;
    case SND_PCM_HOOK_TYPE_CLOSE:    return HookType::close;
    default: break;
    }

    assert(false);
    return static_cast<HookType>(-1);
}


[[maybe_unused]] snd_spcm_latency_t latency2alsa(Latency v) noexcept {
    switch (v) {
    case Latency::standard: return SND_SPCM_LATENCY_STANDARD;
    case Latency::medium:   return SND_SPCM_LATENCY_MEDIUM;
    case Latency::realtime: return SND_SPCM_LATENCY_REALTIME;
    default: break;
    }

    assert(false);
    return static_cast<snd_spcm_latency_t>(-1);
}


[[maybe_unused]] Latency alsa2latency(snd_spcm_latency_t v) noexcept {
    switch (v) {
    case SND_SPCM_LATENCY_STANDARD: return Latency::standard;
    case SND_SPCM_LATENCY_MEDIUM:   return Latency::medium;
    case SND_SPCM_LATENCY_REALTIME: return Latency::realtime;
    default: break;
    }

    assert(false);
    return static_cast<Latency>(-1);
}


[[maybe_unused]] snd_spcm_xrun_type_t xrunType2alsa(XrunType v) noexcept {
    switch (v) {
    case XrunType::ignore: return SND_SPCM_XRUN_IGNORE;
    case XrunType::stop:   return SND_SPCM_XRUN_STOP;
    default: break;
    }

    assert(false);
    return static_cast<snd_spcm_xrun_type_t>(-1);
}


[[maybe_unused]] XrunType alsa2xrunType(snd_spcm_xrun_type_t v) noexcept {
    switch (v) {
    case SND_SPCM_XRUN_IGNORE: return XrunType::ignore;
    case SND_SPCM_XRUN_STOP:   return XrunType::stop;
    default: break;
    }

    assert(false);
    return static_cast<XrunType>(-1);
}


[[maybe_unused]] snd_spcm_duplex_type_t duplexType2alsa(DuplexType v) noexcept {
    switch (v) {
    case DuplexType::liberal:  return SND_SPCM_DUPLEX_LIBERAL;
    case DuplexType::pedantic: return SND_SPCM_DUPLEX_PEDANTIC;
    default: break;
    }

    assert(false);
    return static_cast<snd_spcm_duplex_type_t>(-1);
}


[[maybe_unused]] DuplexType alsa2duplexType(snd_spcm_duplex_type_t v) noexcept {
    switch (v) {
    case SND_SPCM_DUPLEX_LIBERAL:  return DuplexType::liberal;
    case SND_SPCM_DUPLEX_PEDANTIC: return DuplexType::pedantic;
    default: break;
    }

    assert(false);
    return static_cast<DuplexType>(-1);
}

//===========================================================
AudioTstampReport alsa2tstampreport(snd_pcm_audio_tstamp_report_t r) noexcept
{
    return AudioTstampReport{ .valid = r.valid != 0, .actualType = alsa2tstampType(static_cast<snd_pcm_tstamp_type_t>(r.actual_type)),
                              .accuracyIsValid = r.accuracy_report != 0, .accuracy = r.accuracy };
}

snd_pcm_audio_tstamp_config_t tstampconfig2alsa(AudioTstampConfig c) noexcept
{
    return _snd_pcm_audio_tstamp_config { .type_requested = static_cast<unsigned int>(tstampType2alsa(c.typeRequested)),
                                          .report_delay = (c.reportDelay ? 1u : 0u) };
}

AudioTstampConfig alsa2tstampconfig(snd_pcm_audio_tstamp_config_t c) noexcept
{
    return AudioTstampConfig { .typeRequested = alsa2tstampType(static_cast<snd_pcm_tstamp_type_t>(c.type_requested)),
                               .reportDelay = (c.report_delay != 0)};
}

//===========================================================
struct ALSAErrorCategory : public std::error_category 
{
    char const* name() const noexcept override final { return "alsa"; }
    std::string message(int c) const override final  { return ::snd_strerror(c); }
};

std::error_category const& errorCategory() { static ALSAErrorCategory c; return c; }

struct ALSAException : public std::system_error {
    ALSAException(int code) : std::system_error(std::error_code(code, errorCategory()))  {}
    ~ALSAException() = default;
};

template <typename Signed>
Signed throwIfError(Signed r) {
    if (r < 0) {
        throw ALSAException(static_cast<int>(r));
    }

    return r;
}

template <typename T> T* throwIfNull(T* ptr) {
    if (ptr == nullptr) {
        throw ALSAException(-1);
    }

    return ptr;
}

//===========================================================
template <auto F, typename T>
std::string dumphelper(T* _this) {
    auto output = std::invoke([] {
        snd_output_t* r;
        throwIfError(snd_output_buffer_open(&r));
        return std::unique_ptr<snd_output_t, int (*)(snd_output_t*)>(r, snd_output_close);
    });
    throwIfError(F(_this, output.get()));

    return std::invoke([&output] {
        char* str = nullptr;
        auto const n = snd_output_buffer_string(output.get(), &str);
        return std::string(str, str + n);
    });
}
}

//===========================================================
namespace alsa
{
namespace pcm
{

template <> Mask<Access>::Mask() { assert(snd_pcm_access_mask_sizeof() <= sizeof(Mask<Access>)); }
template <> Mask<Access>::Mask(Mask const& o) { snd_pcm_access_mask_copy(this, &o); }
template <> Mask<Access>::~Mask() { snd_pcm_access_mask_free(this); }
template <> Mask<Access> Mask<Access>::none() noexcept { Mask<Access> r; snd_pcm_access_mask_none(&r); return r; }
template <> Mask<Access> Mask<Access>::any () noexcept { Mask<Access> r; snd_pcm_access_mask_any (&r); return r; }
template <> bool Mask<Access>::test(Access a0) { return throwIfError(snd_pcm_access_mask_test(this, access2alsa(a0))) != 0; }
template <> bool Mask<Access>::empty() { return throwIfError(snd_pcm_access_mask_empty(this)) != 0; }
template <> void Mask<Access>::set(Access a0) noexcept { return snd_pcm_access_mask_set(this, access2alsa(a0)); }
template <> void Mask<Access>::reset(Access a0) noexcept { return snd_pcm_access_mask_reset(this, access2alsa(a0)); }

template <> Mask<Format>::Mask() { assert(snd_pcm_format_mask_sizeof() <= sizeof(Mask<Format>)); }
template <> Mask<Format>::Mask(Mask const& o) { snd_pcm_format_mask_copy(this, &o); }
template <> Mask<Format>::~Mask() { snd_pcm_format_mask_free(this); }
template <> Mask<Format> Mask<Format>::none() noexcept { Mask<Format> r; snd_pcm_format_mask_none(&r); return r; }
template <> Mask<Format> Mask<Format>::any () noexcept { Mask<Format> r; snd_pcm_format_mask_any (&r); return r; }
template <> bool Mask<Format>::test(Format a0) { return throwIfError(snd_pcm_format_mask_test(this, format2alsa(a0))) != 0; }
template <> bool Mask<Format>::empty() { return throwIfError(snd_pcm_format_mask_empty(this)) != 0; }
template <> void Mask<Format>::set(Format a0) noexcept { return snd_pcm_format_mask_set(this, format2alsa(a0)); }
template <> void Mask<Format>::reset(Format a0) noexcept { return snd_pcm_format_mask_reset(this, format2alsa(a0)); }

template <> Mask<Subformat>::Mask() { assert(snd_pcm_subformat_mask_sizeof() <= sizeof(Mask<Subformat>)); }
template <> Mask<Subformat>::Mask(Mask const& o) { snd_pcm_subformat_mask_copy(this, &o); }
template <> Mask<Subformat>::~Mask() { snd_pcm_subformat_mask_free(this); }
template <> Mask<Subformat> Mask<Subformat>::none() noexcept { Mask<Subformat> r; snd_pcm_subformat_mask_none(&r); return r; }
template <> Mask<Subformat> Mask<Subformat>::any () noexcept { Mask<Subformat> r; snd_pcm_subformat_mask_any (&r); return r; }
template <> bool Mask<Subformat>::test(Subformat a0) { return throwIfError(snd_pcm_subformat_mask_test(this, subformat2alsa(a0))) != 0; }
template <> bool Mask<Subformat>::empty() { return throwIfError(snd_pcm_subformat_mask_empty(this)) != 0; }
template <> void Mask<Subformat>::set(Subformat a0) noexcept { return snd_pcm_subformat_mask_set(this, subformat2alsa(a0)); }
template <> void Mask<Subformat>::reset(Subformat a0) noexcept { return snd_pcm_subformat_mask_reset(this, subformat2alsa(a0)); }

Info::Info() { assert(snd_pcm_info_sizeof() <= sizeof(Info)); }
Info::Info(Info const& o) { snd_pcm_info_copy(this, &o); }
Info::~Info() {}
unsigned int Info::device() noexcept { return snd_pcm_info_get_device(this); }
unsigned int Info::subdevice() noexcept { return snd_pcm_info_get_subdevice(this); }
Stream Info::stream() noexcept { return alsa2stream(snd_pcm_info_get_stream(this)); }
int Info::card() { return throwIfError(snd_pcm_info_get_card(this)); }
std::string Info::id() { return throwIfNull(snd_pcm_info_get_id(this)); }
std::string Info::name() { return throwIfNull(snd_pcm_info_get_name(this)); }
std::string Info::subdeviceName() { return throwIfNull(snd_pcm_info_get_subdevice_name(this)); }
Class Info::cls() noexcept { return alsa2class(snd_pcm_info_get_class(this)); }
Subclass Info::subclass() noexcept { return alsa2subclass(snd_pcm_info_get_subclass(this)); }
unsigned int Info::subdevicesCount() noexcept { return snd_pcm_info_get_subdevices_count(this); }
unsigned int Info::subdevicesAvail() noexcept { return snd_pcm_info_get_subdevices_avail(this); }
static_assert(std::tuple_size_v<SyncID> == sizeof(snd_pcm_sync_id_t));
SyncID Info::sync() noexcept { snd_pcm_sync_id_t sid = snd_pcm_info_get_sync(this); SyncID r; std::memcpy(r.data(), sid.id16, r.size()); return r; }
void Info::setDevice(unsigned int a0) noexcept { return snd_pcm_info_set_device(this, a0); }
void Info::setSubdevice(unsigned int a0) noexcept { return snd_pcm_info_set_subdevice(this, a0); }
void Info::setStream(Stream a0) noexcept { return snd_pcm_info_set_stream(this, stream2alsa(a0)); }

HWParams::HWParams(Device& d) : device_(d) { assert((snd_pcm_hw_params_sizeof() + sizeof(Device&)) <= sizeof(HWParams)); }
HWParams::HWParams(HWParams const& o) : device_(o.device_) { snd_pcm_hw_params_copy(this, &o); }
HWParams::~HWParams() { snd_pcm_hw_params_free(this); }
HWParams HWParams::current(Device& d) { HWParams r(d); throwIfError(snd_pcm_hw_params_current(d.pcm_.get(), &r)); return r; }
HWParams HWParams::any(Device& d) { HWParams r(d); throwIfError(snd_pcm_hw_params_any(d.pcm_.get(), &r)); return r; }
bool HWParams::canMmapSampleResolution() { return throwIfError(snd_pcm_hw_params_can_mmap_sample_resolution(this)) != 0; }
bool HWParams::isDouble() { return throwIfError(snd_pcm_hw_params_is_double(this)) != 0; }
bool HWParams::isBatch() { return throwIfError(snd_pcm_hw_params_is_batch(this)) != 0; }
bool HWParams::isBlockTransfer() { return throwIfError(snd_pcm_hw_params_is_block_transfer(this)) != 0; }
bool HWParams::isMonotonic() { return throwIfError(snd_pcm_hw_params_is_monotonic(this)) != 0; }
bool HWParams::canOverrange() { return throwIfError(snd_pcm_hw_params_can_overrange(this)) != 0; }
bool HWParams::canPause() { return throwIfError(snd_pcm_hw_params_can_pause(this)) != 0; }
bool HWParams::canResume() { return throwIfError(snd_pcm_hw_params_can_resume(this)) != 0; }
bool HWParams::isHalfDuplex() { return throwIfError(snd_pcm_hw_params_is_half_duplex(this)) != 0; }
bool HWParams::isJointDuplex() { return throwIfError(snd_pcm_hw_params_is_joint_duplex(this)) != 0; }
bool HWParams::canSyncStart() { return throwIfError(snd_pcm_hw_params_can_sync_start(this)) != 0; }
bool HWParams::canDisablePeriodWakeup() { return throwIfError(snd_pcm_hw_params_can_disable_period_wakeup(this)) != 0; }
bool HWParams::isPerfectDrain() { return throwIfError(snd_pcm_hw_params_is_perfect_drain(this)) != 0; }
bool HWParams::supportsAudioWallclockTs() { return throwIfError(snd_pcm_hw_params_supports_audio_wallclock_ts(this)) != 0; }
bool HWParams::supportsAudioTsType(int a0) { return throwIfError(snd_pcm_hw_params_supports_audio_ts_type(this, a0)) != 0; }
Fraction HWParams::rateAsFraction() { Fraction r; throwIfError(snd_pcm_hw_params_get_rate_numden(this, &r.numerator, &r.denominator)); return r; }
int HWParams::sbits() { return throwIfError(snd_pcm_hw_params_get_sbits(this)); }
int HWParams::fifoSize() { return throwIfError(snd_pcm_hw_params_get_fifo_size(this)); }
Access HWParams::access() { snd_pcm_access_t r; snd_pcm_hw_params_get_access(this, &r); return alsa2access(r); }
bool HWParams::testAccess(Access a0) { return throwIfError(snd_pcm_hw_params_test_access(device_.pcm_.get(), this, access2alsa(a0))) != 0; }
void HWParams::setAccess(Access a0) { throwIfError(snd_pcm_hw_params_set_access(device_.pcm_.get(), this, access2alsa(a0))); }
void HWParams::setAccessFirst(Access& a0) { auto a = access2alsa(a0); throwIfError(snd_pcm_hw_params_set_access_first(device_.pcm_.get(), this, &a)); a0 = alsa2access(a); }
void HWParams::setAccessLast(Access& a0)  { auto a = access2alsa(a0); throwIfError(snd_pcm_hw_params_set_access_last(device_.pcm_.get(), this, &a)); a0 = alsa2access(a); }
void HWParams::setAccessMask(Mask<Access>& a0) { throwIfError(snd_pcm_hw_params_set_access_mask(device_.pcm_.get(), this, &a0)); }
Mask<Access> HWParams::accessMask() { Mask<Access> r; throwIfError(snd_pcm_hw_params_get_access_mask(this, &r)); return r; }
Format HWParams::format() { snd_pcm_format_t r; snd_pcm_hw_params_get_format(this, &r); return alsa2format(r); }
bool HWParams::testFormat(Format a0) { return throwIfError(snd_pcm_hw_params_test_format(device_.pcm_.get(), this, format2alsa(a0))) != 0; }
void HWParams::setFormat(Format a0) { throwIfError(snd_pcm_hw_params_set_format(device_.pcm_.get(), this, format2alsa(a0))); }
void HWParams::setFormatFirst(Format& a0) { auto f = format2alsa(a0); throwIfError(snd_pcm_hw_params_set_format_first(device_.pcm_.get(), this, &f)); a0 = alsa2format(f); }
void HWParams::setFormatLast(Format& a0) { auto f = format2alsa(a0); throwIfError(snd_pcm_hw_params_set_format_last(device_.pcm_.get(), this, &f)); a0 = alsa2format(f); }
void HWParams::setFormatMask(Mask<Format>& a0) { throwIfError(snd_pcm_hw_params_set_format_mask(device_.pcm_.get(), this, &a0)); }
Mask<Format> HWParams::formatMask() noexcept { Mask<Format> r; snd_pcm_hw_params_get_format_mask(this, &r); return r; }
Subformat HWParams::subformat() { snd_pcm_subformat_t r; snd_pcm_hw_params_get_subformat(this, &r); return alsa2subformat(r); }
bool HWParams::testSubformat(Subformat a0) { return throwIfError(snd_pcm_hw_params_test_subformat(device_.pcm_.get(), this, subformat2alsa(a0))) != 0; }
void HWParams::setSubformat(Subformat a0) { throwIfError(snd_pcm_hw_params_set_subformat(device_.pcm_.get(), this, subformat2alsa(a0))); }
void HWParams::setSubformatFirst(Subformat& a0) { auto s = subformat2alsa(a0); throwIfError(snd_pcm_hw_params_set_subformat_first(device_.pcm_.get(), this, &s)); a0 = alsa2subformat(s); }
void HWParams::setSubformatLast(Subformat& a0) { auto s = subformat2alsa(a0); throwIfError(snd_pcm_hw_params_set_subformat_last(device_.pcm_.get(), this, &s)); a0 = alsa2subformat(s); }
void HWParams::setSubformatMask(Mask<Subformat>& a0) { throwIfError(snd_pcm_hw_params_set_subformat_mask(device_.pcm_.get(), this, &a0)); }
Mask<Subformat> HWParams::subformatMask() noexcept { Mask<Subformat> r; snd_pcm_hw_params_get_subformat_mask(this, &r); return r; }
unsigned int HWParams::channels() { unsigned int r; throwIfError(snd_pcm_hw_params_get_channels(this, &r)); return r; }
unsigned int HWParams::channelsMin() { unsigned int r; throwIfError(snd_pcm_hw_params_get_channels_min(this, &r)); return r; }
unsigned int HWParams::channelsMax() { unsigned int r; throwIfError(snd_pcm_hw_params_get_channels_max(this, &r)); return r; }
bool HWParams::testChannels(unsigned int a0) { return throwIfError(snd_pcm_hw_params_test_channels(device_.pcm_.get(), this, a0)) != 0; }
void HWParams::setChannels(unsigned int a0) { throwIfError(snd_pcm_hw_params_set_channels(device_.pcm_.get(), this, a0)); }
void HWParams::setChannelsMin(unsigned int& a0) { throwIfError(snd_pcm_hw_params_set_channels_min(device_.pcm_.get(), this, &a0)); }
void HWParams::setChannelsMax(unsigned int& a0) { throwIfError(snd_pcm_hw_params_set_channels_max(device_.pcm_.get(), this, &a0)); }
void HWParams::setChannelsMinmax(unsigned int& a0, unsigned int& a1) { throwIfError(snd_pcm_hw_params_set_channels_minmax(device_.pcm_.get(), this, &a0, &a1)); }
void HWParams::setChannelsNear(unsigned int& a0) { throwIfError(snd_pcm_hw_params_set_channels_near(device_.pcm_.get(), this, &a0)); }
void HWParams::setChannelsFirst(unsigned int& a0) { throwIfError(snd_pcm_hw_params_set_channels_first(device_.pcm_.get(), this, &a0)); }
void HWParams::setChannelsLast(unsigned int& a0) { throwIfError(snd_pcm_hw_params_set_channels_last(device_.pcm_.get(), this, &a0)); }
UValDir HWParams::rate() { UValDir r; throwIfError(snd_pcm_hw_params_get_rate(this, &r.value, &r.direction)); return r; }
UValDir HWParams::rateMin() { UValDir r; throwIfError(snd_pcm_hw_params_get_rate_min(this, &r.value, &r.direction)); return r; }
UValDir HWParams::rateMax() { UValDir r; throwIfError(snd_pcm_hw_params_get_rate_max(this, &r.value, &r.direction)); return r; }
bool HWParams::testRate(ValDir const& a0) { return throwIfError(snd_pcm_hw_params_test_rate(device_.pcm_.get(), this, a0.value, a0.direction)) != 0; }
void HWParams::setRate(ValDir const& a0) { throwIfError(snd_pcm_hw_params_set_rate(device_.pcm_.get(), this, a0.value, a0.direction)); }
void HWParams::setRateMin(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_rate_min(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setRateMax(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_rate_max(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setRateMinmax(UValDir& a0, UValDir& a1) { throwIfError(snd_pcm_hw_params_set_rate_minmax(device_.pcm_.get(), this, &a0.value, &a0.direction, &a1.value, &a1.direction)); }
void HWParams::setRateNear(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_rate_near(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setRateFirst(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_rate_first(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setRateLast(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_rate_last(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setRateResample(unsigned int a0) { throwIfError(snd_pcm_hw_params_set_rate_resample(device_.pcm_.get(), this, a0)); }
unsigned int HWParams::rateResample() { unsigned int r; throwIfError(snd_pcm_hw_params_get_rate_resample(device_.pcm_.get(), this, &r)); return r; }
void HWParams::setExportBuffer(unsigned int a0) { throwIfError(snd_pcm_hw_params_set_export_buffer(device_.pcm_.get(), this, a0)); }
unsigned int HWParams::exportBuffer() { unsigned int r; throwIfError(snd_pcm_hw_params_get_export_buffer(device_.pcm_.get(), this, &r)); return r; }
void HWParams::setPeriodWakeup(unsigned int a0) { throwIfError(snd_pcm_hw_params_set_period_wakeup(device_.pcm_.get(), this, a0)); }
unsigned int HWParams::periodWakeup() { unsigned int r; throwIfError(snd_pcm_hw_params_get_period_wakeup(device_.pcm_.get(), this, &r)); return r; }
void HWParams::setDrainSilence(unsigned int a0) { throwIfError(snd_pcm_hw_params_set_drain_silence(device_.pcm_.get(), this, a0)); }
unsigned int HWParams::drainSilence() { unsigned int r; throwIfError(snd_pcm_hw_params_get_drain_silence(device_.pcm_.get(), this, &r)); return r; }
UValDir HWParams::periodTime() { UValDir r; throwIfError(snd_pcm_hw_params_get_period_time(this, &r.value, &r.direction)); return r; }
UValDir HWParams::periodTimeMin() { UValDir r; throwIfError(snd_pcm_hw_params_get_period_time_min(this, &r.value, &r.direction)); return r; }
UValDir HWParams::periodTimeMax() { UValDir r; throwIfError(snd_pcm_hw_params_get_period_time_max(this, &r.value, &r.direction)); return r; }
bool HWParams::testPeriodTime(ValDir const& a0) { return throwIfError(snd_pcm_hw_params_test_period_time(device_.pcm_.get(), this, a0.value, a0.direction)) != 0; }
void HWParams::setPeriodTime(ValDir const& a0) { throwIfError(snd_pcm_hw_params_set_period_time(device_.pcm_.get(), this, a0.value, a0.direction)); }
void HWParams::setPeriodTimeMin(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_time_min(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodTimeMax(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_time_max(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodTimeMinmax(UValDir& a0, UValDir& a1) { throwIfError(snd_pcm_hw_params_set_period_time_minmax(device_.pcm_.get(), this, &a0.value, &a0.direction, &a1.value, &a1.direction)); }
void HWParams::setPeriodTimeNear(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_time_near(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodTimeFirst(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_time_first(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodTimeLast(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_time_last(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
UFramesValDir HWParams::periodSize() { UFramesValDir r; throwIfError(snd_pcm_hw_params_get_period_size(this, &r.value, &r.direction)); return r; }
UFramesValDir HWParams::periodSizeMin() { UFramesValDir r; throwIfError(snd_pcm_hw_params_get_period_size_min(this, &r.value, &r.direction)); return r; }
UFramesValDir HWParams::periodSizeMax() { UFramesValDir r; throwIfError(snd_pcm_hw_params_get_period_size_max(this, &r.value, &r.direction)); return r; }
bool HWParams::testPeriodSize(ValDir const& a0) { return throwIfError(snd_pcm_hw_params_test_period_size(device_.pcm_.get(), this, a0.value, a0.direction)) != 0; }
void HWParams::setPeriodSize(ValDir const& a0) { throwIfError(snd_pcm_hw_params_set_period_size(device_.pcm_.get(), this, a0.value, a0.direction)); }
void HWParams::setPeriodSizeMin(UFramesValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_size_min(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodSizeMax(UFramesValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_size_max(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodSizeMinmax(UFramesValDir& a0, UFramesValDir& a1) { throwIfError(snd_pcm_hw_params_set_period_size_minmax(device_.pcm_.get(), this, &a0.value, &a0.direction, &a1.value, &a1.direction)); }
void HWParams::setPeriodSizeNear(UFramesValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_size_near(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodSizeFirst(UFramesValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_size_first(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodSizeLast(UFramesValDir& a0) { throwIfError(snd_pcm_hw_params_set_period_size_last(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodSizeInteger() { throwIfError(snd_pcm_hw_params_set_period_size_integer(device_.pcm_.get(), this)); }
UValDir HWParams::periods() { UValDir r; throwIfError(snd_pcm_hw_params_get_periods(this, &r.value, &r.direction)); return r; }
UValDir HWParams::periodsMin() { UValDir r; throwIfError(snd_pcm_hw_params_get_periods_min(this, &r.value, &r.direction)); return r; }
UValDir HWParams::periodsMax() { UValDir r; throwIfError(snd_pcm_hw_params_get_periods_max(this, &r.value, &r.direction)); return r; }
bool HWParams::testPeriods(ValDir const& a0) { return throwIfError(snd_pcm_hw_params_test_periods(device_.pcm_.get(), this, a0.value, a0.direction)) != 0; }
void HWParams::setPeriods(ValDir const& a0) { throwIfError(snd_pcm_hw_params_set_periods(device_.pcm_.get(), this, a0.value, a0.direction)); }
void HWParams::setPeriodsMin(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_periods_min(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodsMax(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_periods_max(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodsMinmax(UValDir& a0, UValDir& a1) { throwIfError(snd_pcm_hw_params_set_periods_minmax(device_.pcm_.get(), this, &a0.value, &a0.direction, &a1.value, &a1.direction)); }
void HWParams::setPeriodsNear(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_periods_near(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodsFirst(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_periods_first(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodsLast(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_periods_last(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setPeriodsInteger() { throwIfError(snd_pcm_hw_params_set_periods_integer(device_.pcm_.get(), this)); }
UValDir HWParams::bufferTime() { UValDir r; throwIfError(snd_pcm_hw_params_get_buffer_time(this, &r.value, &r.direction)); return r; }
UValDir HWParams::bufferTimeMin() { UValDir r; throwIfError(snd_pcm_hw_params_get_buffer_time_min(this, &r.value, &r.direction)); return r; }
UValDir HWParams::bufferTimeMax() { UValDir r; throwIfError(snd_pcm_hw_params_get_buffer_time_max(this, &r.value, &r.direction)); return r; }
bool HWParams::testBufferTime(ValDir const& a0) { return throwIfError(snd_pcm_hw_params_test_buffer_time(device_.pcm_.get(), this, a0.value, a0.direction)) != 0; }
void HWParams::setBufferTime(ValDir const& a0) { throwIfError(snd_pcm_hw_params_set_buffer_time(device_.pcm_.get(), this, a0.value, a0.direction)); }
void HWParams::setBufferTimeMin(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_buffer_time_min(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setBufferTimeMax(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_buffer_time_max(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setBufferTimeMinmax(UValDir& a0, UValDir& a1) { throwIfError(snd_pcm_hw_params_set_buffer_time_minmax(device_.pcm_.get(), this, &a0.value, &a0.direction, &a1.value, &a1.direction)); }
void HWParams::setBufferTimeNear(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_buffer_time_near(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setBufferTimeFirst(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_buffer_time_first(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
void HWParams::setBufferTimeLast(UValDir& a0) { throwIfError(snd_pcm_hw_params_set_buffer_time_last(device_.pcm_.get(), this, &a0.value, &a0.direction)); }
UFrames HWParams::bufferSize() { UFrames r; throwIfError(snd_pcm_hw_params_get_buffer_size(this, &r)); return r; }
UFrames HWParams::bufferSizeMin() { UFrames r; throwIfError(snd_pcm_hw_params_get_buffer_size_min(this, &r)); return r; }
UFrames HWParams::bufferSizeMax() { UFrames r; throwIfError(snd_pcm_hw_params_get_buffer_size_max(this, &r)); return r; }
bool HWParams::testBufferSize(UFrames a0) { return throwIfError(snd_pcm_hw_params_test_buffer_size(device_.pcm_.get(), this, a0)) != 0; }
void HWParams::setBufferSize(UFrames a0) { throwIfError(snd_pcm_hw_params_set_buffer_size(device_.pcm_.get(), this, a0)); }
void HWParams::setBufferSizeMin(UFrames& a0) { throwIfError(snd_pcm_hw_params_set_buffer_size_min(device_.pcm_.get(), this, &a0)); }
void HWParams::setBufferSizeMax(UFrames& a0) { throwIfError(snd_pcm_hw_params_set_buffer_size_max(device_.pcm_.get(), this, &a0)); }
void HWParams::setBufferSizeMinmax(UFrames& a0, UFrames& a1) { throwIfError(snd_pcm_hw_params_set_buffer_size_minmax(device_.pcm_.get(), this, &a0, &a1)); }
void HWParams::setBufferSizeNear(UFrames& a0) { throwIfError(snd_pcm_hw_params_set_buffer_size_near(device_.pcm_.get(), this, &a0)); }
void HWParams::setBufferSizeFirst(UFrames& a0) { throwIfError(snd_pcm_hw_params_set_buffer_size_first(device_.pcm_.get(), this, &a0)); }
void HWParams::setBufferSizeLast(UFrames& a0) { throwIfError(snd_pcm_hw_params_set_buffer_size_last(device_.pcm_.get(), this, &a0)); }
UFrames HWParams::minAlign() { UFrames r; throwIfError(snd_pcm_hw_params_get_min_align(this, &r)); return r; }
std::string HWParams::dump() { return dumphelper<snd_pcm_hw_params_dump>(static_cast<snd_pcm_hw_params_t*>(this)); }

SWParams::SWParams(Device& d) : device_(d) { assert((snd_pcm_sw_params_sizeof() + sizeof(Device&)) <= sizeof(SWParams)); }
SWParams::SWParams(SWParams const& o) : device_(o.device_) { snd_pcm_sw_params_copy(this, &o); }
SWParams::~SWParams() { snd_pcm_sw_params_free(this); }
SWParams SWParams::current(Device& d) { SWParams r(d); throwIfError(snd_pcm_sw_params_current(d.pcm_.get(), &r)); return r; }
UFrames SWParams::boundary() { UFrames r; throwIfError(snd_pcm_sw_params_get_boundary(this, &r)); return r; }
void SWParams::setTstampMode(Tstamp a0) { throwIfError(snd_pcm_sw_params_set_tstamp_mode(device_.pcm_.get(), this, tstamp2alsa(a0))); }
Tstamp SWParams::tstampMode() { snd_pcm_tstamp_t r; snd_pcm_sw_params_get_tstamp_mode(this, &r); return alsa2tstamp(r); }
void SWParams::setTstampType(TstampType a0) { throwIfError(snd_pcm_sw_params_set_tstamp_type(device_.pcm_.get(), this, tstampType2alsa(a0))); }
TstampType SWParams::tstampType() { snd_pcm_tstamp_type_t r; snd_pcm_sw_params_get_tstamp_type(this, &r); return alsa2tstampType(r); }
void SWParams::setAvailMin(UFrames a0) { throwIfError(snd_pcm_sw_params_set_avail_min(device_.pcm_.get(), this, a0)); }
UFrames SWParams::availMin() { UFrames r; throwIfError(snd_pcm_sw_params_get_avail_min(this, &r)); return r; }
void SWParams::setPeriodEvent(int a0) { throwIfError(snd_pcm_sw_params_set_period_event(device_.pcm_.get(), this, a0)); }
int SWParams::periodEvent() { int r; throwIfError(snd_pcm_sw_params_get_period_event(this, &r)); return r; }
void SWParams::setStartThreshold(UFrames a0) { throwIfError(snd_pcm_sw_params_set_start_threshold(device_.pcm_.get(), this, a0)); }
UFrames SWParams::startThreshold() { UFrames r; throwIfError(snd_pcm_sw_params_get_start_threshold(this, &r)); return r; }
void SWParams::setStopThreshold(UFrames a0) { throwIfError(snd_pcm_sw_params_set_stop_threshold(device_.pcm_.get(), this, a0)); }
UFrames SWParams::stopThreshold() { UFrames r; throwIfError(snd_pcm_sw_params_get_stop_threshold(this, &r)); return r; }
void SWParams::setSilenceThreshold(UFrames a0) { throwIfError(snd_pcm_sw_params_set_silence_threshold(device_.pcm_.get(), this, a0)); }
UFrames SWParams::silenceThreshold() { UFrames r; throwIfError(snd_pcm_sw_params_get_silence_threshold(this, &r)); return r; }
void SWParams::setSilenceSize(UFrames a0) { throwIfError(snd_pcm_sw_params_set_silence_size(device_.pcm_.get(), this, a0)); }
UFrames SWParams::silenceSize() { UFrames r; throwIfError(snd_pcm_sw_params_get_silence_size(this, &r)); return r; }
std::string SWParams::dump() { return dumphelper<snd_pcm_sw_params_dump>(static_cast<snd_pcm_sw_params_t*>(this)); }

Status::Status() { assert(snd_pcm_status_sizeof() <= sizeof(Status)); }
Status::Status(Status const& o) { snd_pcm_status_copy(this, &o); }
Status::~Status() { snd_pcm_status_free(this); }
State Status::state() noexcept { return alsa2state(snd_pcm_status_get_state(this)); }
::timespec Status::triggerTstamp() noexcept { snd_htimestamp_t r; snd_pcm_status_get_trigger_htstamp(this, &r); return r; }
::timespec Status::tstamp() noexcept { snd_htimestamp_t r; snd_pcm_status_get_htstamp(this, &r); return r; }
::timespec Status::audioTstamp() noexcept { snd_htimestamp_t r; snd_pcm_status_get_audio_htstamp(this, &r); return r; }
::timespec Status::driverTstamp() noexcept { snd_htimestamp_t r; snd_pcm_status_get_driver_htstamp(this, &r); return r; }
AudioTstampReport Status::audioHtstampReport() noexcept { snd_pcm_audio_tstamp_report_t r; snd_pcm_status_get_audio_htstamp_report(this, &r); return alsa2tstampreport(r); }
void Status::setAudioHtstampConfig(AudioTstampConfig& a0) noexcept { auto c = tstampconfig2alsa(a0); snd_pcm_status_set_audio_htstamp_config(this, &c); a0 = alsa2tstampconfig(c); }
SFrames Status::delay() noexcept { return snd_pcm_status_get_delay(this); }
UFrames Status::avail() noexcept { return snd_pcm_status_get_avail(this); }
UFrames Status::availMax() noexcept { return snd_pcm_status_get_avail_max(this); }
UFrames Status::overrange() noexcept { return snd_pcm_status_get_overrange(this); }
std::string Status::dump() { return dumphelper<snd_pcm_status_dump>(static_cast<snd_pcm_status_t*>(this)); }

Device::Device(char const* name, Stream stream, int mode) 
    : pcm_(std::invoke([&] {
        snd_pcm_t* r;
        throwIfError(snd_pcm_open(&r, name, stream2alsa(stream), mode));
        return std::unique_ptr<struct _snd_pcm, int (*)(struct _snd_pcm*)>(r, snd_pcm_close);
    })) {}
Device::~Device() = default;
std::string Device::name() { return throwIfNull(snd_pcm_name(pcm_.get())); }
Type Device::type() noexcept { return alsa2type(snd_pcm_type(pcm_.get())); }
Stream Device::stream() noexcept { return alsa2stream(snd_pcm_stream(pcm_.get())); }
Info Device::info() { Info r; throwIfError(snd_pcm_info(pcm_.get(), &r)); return r; }
void Device::apply(HWParams& a0) { throwIfError(snd_pcm_hw_params(pcm_.get(), &a0)); }
void Device::apply(SWParams& a0) { throwIfError(snd_pcm_sw_params(pcm_.get(), &a0)); }
void Device::prepare() { throwIfError(snd_pcm_prepare(pcm_.get())); }
void Device::reset() { throwIfError(snd_pcm_reset(pcm_.get())); }
Status Device::status() { Status r; throwIfError(snd_pcm_status(pcm_.get(), &r)); return r; }
void Device::start() { throwIfError(snd_pcm_start(pcm_.get())); }
void Device::drop() { throwIfError(snd_pcm_drop(pcm_.get())); }
void Device::drain() { throwIfError(snd_pcm_drain(pcm_.get())); }
void Device::pause(bool a0) { throwIfError(snd_pcm_pause(pcm_.get(), a0 ? 1 : 0)); }
State Device::state() noexcept { return alsa2state(snd_pcm_state(pcm_.get())); }
void Device::link(Device& a0, Device& a1) { throwIfError(snd_pcm_link(a0.pcm_.get(), a1.pcm_.get())); }
void Device::unlink() { throwIfError(snd_pcm_unlink(pcm_.get())); }
UFrames Device::avail() { return static_cast<UFrames>(throwIfError(snd_pcm_avail(pcm_.get()))); }
} // namespace pcm

namespace ctl
{

CardInfo::CardInfo() { assert(sizeof(CardInfo) >= snd_ctl_card_info_sizeof()); }
CardInfo::CardInfo(CardInfo const& o) { snd_ctl_card_info_copy(this, &o); }
CardInfo::~CardInfo() { snd_ctl_card_info_free(this); }
void CardInfo::clear() noexcept { return snd_ctl_card_info_clear(this); }
int CardInfo::card() { return throwIfError(snd_ctl_card_info_get_card(this)); }
std::string CardInfo::id() { return throwIfNull(snd_ctl_card_info_get_id(this)); }
std::string CardInfo::driver() { return throwIfNull(snd_ctl_card_info_get_driver(this)); }
std::string CardInfo::name() { return throwIfNull(snd_ctl_card_info_get_name(this)); }
std::string CardInfo::longname() { return throwIfNull(snd_ctl_card_info_get_longname(this)); }
std::string CardInfo::mixername() { return throwIfNull(snd_ctl_card_info_get_mixername(this)); }
std::string CardInfo::components() { return throwIfNull(snd_ctl_card_info_get_components(this)); }

Cards::Iterator Cards::begin() { auto idx = -1; if (snd_card_next(&idx) < 0) idx = -1; return Iterator(idx); }
Cards::Iterator Cards::end() { return Iterator(-1); }
Cards::Iterator::Iterator(int idx) : idx_(idx) {}
Cards::Iterator::~Iterator() = default;
Cards::Iterator::value_type Cards::Iterator::operator*() { return Value(idx_); }
Cards::Iterator::ValuePointer Cards::Iterator::operator->() { return ValuePointer(idx_); }
Cards::Iterator& Cards::Iterator::Iterator::operator++() { if (snd_card_next(&idx_) < 0) idx_ = -1; return *this; }
Cards::Iterator Cards::Iterator::operator++(int) { auto idx = idx_; if (snd_card_next(&idx) < 0) idx = -1; return Cards::Iterator(idx); }
bool Cards::Iterator::operator==(const Cards::Iterator& o) const noexcept { return idx_ == o.idx_; }
bool Cards::Iterator::operator!=(const Cards::Iterator& o) const noexcept { return idx_ != o.idx_; }
Cards::Iterator::ValuePointer::ValuePointer(int idx) : value_(idx) {}
Cards::Iterator::Value::Value(int idx) : idx__(idx) {}
int Cards::Iterator::Value::index() noexcept { return idx__; }
std::string Cards::Iterator::Value::name() { char* n; throwIfError(snd_card_get_name(idx__, &n)); std::string r(n); ::free(n); return r; }
std::string Cards::Iterator::Value::longname() { char* n; throwIfError(snd_card_get_longname(idx__, &n)); std::string r(n); ::free(n); return r; }

Control::Devices::Iterator::Iterator(Control* ctl, int idx) : ctl_(ctl), idx_(idx) {}
Control::Devices::Iterator::~Iterator() = default;
int Control::Devices::Iterator::operator*() { return idx_; }
Control::Devices::Iterator::ValuePointer Control::Devices::Iterator::operator->() { return ValuePointer(idx_); }
Control::Devices::Iterator& Control::Devices::Iterator::operator++() { if (ctl_ == nullptr || snd_ctl_pcm_next_device(ctl_->ctl_.get(), &idx_) < 0) idx_ = -1; return *this; }
Control::Devices::Iterator Control::Devices::Iterator::operator++(int) { auto idx = idx_; if (ctl_ == nullptr || snd_ctl_pcm_next_device(ctl_->ctl_.get(), &idx_) < 0) idx = -1; return Control::Devices::Iterator(ctl_, idx); }
bool Control::Devices::Iterator::operator==(const Control::Devices::Iterator& o) const noexcept { if (idx_ < 0 && o.idx_ < 0) return true;  return ctl_ == o.ctl_ && idx_ == o.idx_; }
bool Control::Devices::Iterator::operator!=(const Control::Devices::Iterator& o) const noexcept { if (idx_ < 0 && o.idx_ < 0) return false; return ctl_ != o.ctl_ || idx_ != o.idx_; }
Control::Devices::Iterator::ValuePointer::ValuePointer(int idx) : value_(idx) {}

Control::Control(std::string const& name, int mode) 
    : ctl_(std::invoke([&] {
        snd_ctl_t* r;
        throwIfError(snd_ctl_open(&r, name.c_str(), mode));
        return std::unique_ptr<snd_ctl_t, int (*)(snd_ctl_t*)>(r, snd_ctl_close);
    })) {}
Control::~Control() = default;
CardInfo Control::info() { CardInfo i; throwIfError(snd_ctl_card_info(ctl_.get(), &i)); return i; }
void Control::info(pcm::Info& i) { throwIfError(snd_ctl_pcm_info(ctl_.get(), &i)); }
Control::Devices Control::devices() { return Devices(*this); }
Control::Devices::Devices(Control& ctl) : ctl__(ctl) {}
Control::Devices::Iterator Control::Devices::begin() { auto r = -1; throwIfError(snd_ctl_pcm_next_device(ctl__.ctl_.get(), &r)); return Control::Devices::Iterator(&ctl__, r); }
Control::Devices::Iterator Control::Devices::end() { return Control::Devices::Iterator(nullptr, -1); }
} // namespace ctl
} // namespace alsa