//
//  cxxalsa.hpp
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
// This header was auto generated from ALSA's C API with
// the tool created from autogenerate.cpp in the cxxalsa
// repo
//===========================================================

#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <array>
#include <memory>
#include <sys/time.h>

//===========================================================
// Storage requirements
struct _snd_pcm;
struct _snd_ctl;
struct _snd_pcm_info { alignas(16) std::byte _storage[288] = {}; };
struct _snd_pcm_hw_params { alignas(16) std::byte _storage[608] = {}; };
struct _snd_pcm_sw_params { alignas(16) std::byte _storage[136] = {}; };
struct _snd_pcm_status { alignas(16) std::byte _storage[152] = {}; };
struct _snd_pcm_access_mask { alignas(16) std::byte _storage[32] = {}; };
struct _snd_pcm_format_mask { alignas(16) std::byte _storage[32] = {}; };
struct _snd_pcm_subformat_mask { alignas(16) std::byte _storage[32] = {}; };
struct _snd_ctl_card_info { alignas(16) std::byte _storage[376] = {}; };

//===========================================================
namespace alsa
{

//===========================================================
// Forward declarations from ctl
namespace ctl
{
class Control;
} // namespace ctl

namespace pcm
{

//===========================================================
// primitive type definitions
using UFrames = unsigned long;
using SFrames = long;

//===========================================================
// enums
enum class Class {
    generic,
    multi,
    modem,
    digitizer
};

enum class Subclass {
    genericMix,
    multiMix
};

enum class Stream {
    playback,
    capture
};

enum class Access {
    mmapInterleaved,
    mmapNoninterleaved,
    mmapComplex,
    rwInterleaved,
    rwNoninterleaved
};

enum class Format {
    unknown,
    s8,
    u8,
    s16Le,
    s16Be,
    u16Le,
    u16Be,
    s24Le,
    s24Be,
    u24Le,
    u24Be,
    s32Le,
    s32Be,
    u32Le,
    u32Be,
    floatLe,
    floatBe,
    float64Le,
    float64Be,
    iec958SubframeLe,
    iec958SubframeBe,
    muLaw,
    aLaw,
    imaAdpcm,
    mpeg,
    gsm,
    s20Le,
    s20Be,
    u20Le,
    u20Be,
    special,
    s243le,
    s243be,
    u243le,
    u243be,
    s203le,
    s203be,
    u203le,
    u203be,
    s183le,
    s183be,
    u183le,
    u183be,
    g72324,
    g723241b,
    g72340,
    g723401b,
    dsdU8,
    dsdU16Le,
    dsdU32Le,
    dsdU16Be,
    dsdU32Be,
    float32,
    float64,
    iec958Subframe,
    s20,
    u20
};

enum class Subformat {
    unknown,
    std,
    msbitsMax,
    msbits20,
    msbits24
};

enum class State {
    open,
    setup,
    prepared,
    running,
    xrun,
    draining,
    paused,
    suspended,
    disconnected
};

enum class Start {
    data,
    explicitly
};

enum class Xrun {
    none,
    stop
};

enum class Tstamp {
    none,
    enable
};

enum class TstampType {
    gettimeofday,
    monotonic,
    monotonicRaw
};

enum class AudioTstampType {
    compat,
    dflt,
    link,
    linkAbsolute,
    linkEstimated,
    linkSynchronized
};

enum class Type {
    hw,
    hooks,
    multi,
    file,
    null,
    shm,
    inet,
    copy,
    linear,
    alaw,
    mulaw,
    adpcm,
    rate,
    route,
    plug,
    share,
    meter,
    mix,
    droute,
    lbserver,
    linearFloat,
    ladspa,
    dmix,
    jack,
    dsnoop,
    dshare,
    iec958,
    softvol,
    ioplug,
    extplug,
    mmapEmul
};

enum class ChmapTy {
    none,
    fixed,
    var,
    paired
};

enum class ChmapPositi {
    unknown,
    na,
    mono,
    fl,
    fr,
    rl,
    rr,
    fc,
    lfe,
    sl,
    sr,
    rc,
    flc,
    frc,
    rlc,
    rrc,
    flw,
    frw,
    flh,
    fch,
    frh,
    tc,
    tfl,
    tfr,
    tfc,
    trl,
    trr,
    trc,
    tflc,
    tfrc,
    tsl,
    tsr,
    llfe,
    rlfe,
    bc,
    blc,
    brc
};

enum class HookType {
    hwParams,
    hwFree,
    close
};

enum class Latency {
    standard,
    medium,
    realtime
};

enum class XrunType {
    ignore,
    stop
};

enum class DuplexType {
    liberal,
    pedantic
};

//===========================================================
// POD structs
struct ValDir
{
    int value;
    int direction;
};

struct UValDir
{
    unsigned int value;
    int direction;
};

struct UFramesValDir
{
    UFrames value;
    int direction;
};

struct Fraction
{
    unsigned int numerator;
    unsigned int denominator;
};

struct AudioTstampConfig {
	TstampType typeRequested; /**< requested audio tstamp type */
	bool reportDelay; /**< add total delay to A/D or D/A */
};

struct AudioTstampReport {
	bool valid; /**< for backwards compatibility */
	TstampType actualType; /**< actual type if hardware could not support requested timestamp */

	bool accuracyIsValid; /**< 0 if accuracy unknown, 1 if accuracy field is valid */
	unsigned int accuracy; /**< up to 4.29s in ns units, will be packed in separate field  */
};

using SyncID = std::array<std::uint8_t, 16>;

//===========================================================
// Forward declarations
class Device;
class HWParams;
class SWParams;

namespace detail
{
template <typename> struct MaskType;
template <> struct MaskType<Access>    { using type = _snd_pcm_access_mask; };
template <> struct MaskType<Format>    { using type = _snd_pcm_format_mask; };
template <> struct MaskType<Subformat> { using type = _snd_pcm_subformat_mask; };
}

//===========================================================
// Objects
template <typename Type>
class Mask : private detail::MaskType<Type>::type {
    Mask(Mask const& o);
    ~Mask();

    static Mask none() noexcept;
    static Mask any() noexcept;

    bool test(Type val);
    bool empty();
    void set(Type val) noexcept;
    void reset(Type val) noexcept;
private:
    friend class HWParams;
    friend class SWParams;
    Mask();
};

class Info : private _snd_pcm_info {
public:
    Info();
    Info(Info const& o);
    ~Info();

    unsigned int device() noexcept;
    unsigned int subdevice() noexcept;
    Stream stream() noexcept;
    int card();
    std::string id();
    std::string name();
    std::string subdeviceName();
    Class cls() noexcept;
    Subclass subclass() noexcept;
    unsigned int subdevicesCount() noexcept;
    unsigned int subdevicesAvail() noexcept;
    SyncID sync() noexcept;
    void setDevice(unsigned int val) noexcept;
    void setSubdevice(unsigned int val) noexcept;
    void setStream(Stream val) noexcept;

private:
    friend class Device;
    friend class ctl::Control;
};

class HWParams : private _snd_pcm_hw_params {
public:
    HWParams(HWParams const& o);
    ~HWParams();

    static HWParams current(Device&);
    static HWParams any(Device&);

    bool canMmapSampleResolution();
    bool isDouble();
    bool isBatch();
    bool isBlockTransfer();
    bool isMonotonic();
    bool canOverrange();
    bool canPause();
    bool canResume();
    bool isHalfDuplex();
    bool isJointDuplex();
    bool canSyncStart();
    bool canDisablePeriodWakeup();
    bool isPerfectDrain();
    bool supportsAudioWallclockTs();
    bool supportsAudioTsType(int type);
    Fraction rateAsFraction();
    int sbits();
    int fifoSize();
    Access access();
    bool testAccess(Access access);
    void setAccess(Access access);
    void setAccessFirst(Access& access);
    void setAccessLast(Access& access);
    void setAccessMask(Mask<Access>& mask);
    Mask<Access> accessMask();
    Format format();
    bool testFormat(Format val);
    void setFormat(Format val);
    void setFormatFirst(Format& format);
    void setFormatLast(Format&  format);
    void setFormatMask(Mask<Format>& mask);
    Mask<Format> formatMask() noexcept;
    Subformat subformat();
    bool testSubformat(Subformat subformat);
    void setSubformat(Subformat subformat);
    void setSubformatFirst(Subformat& subformat);
    void setSubformatLast(Subformat& subformat);
    void setSubformatMask(Mask<Subformat>& mask);
    Mask<Subformat> subformatMask() noexcept;
    unsigned int channels();
    unsigned int channelsMin();
    unsigned int channelsMax();
    bool testChannels(unsigned int val);
    void setChannels(unsigned int val);
    void setChannelsMin(unsigned int& val);
    void setChannelsMax(unsigned int& val);
    void setChannelsMinmax(unsigned int& min, unsigned int& max);
    void setChannelsNear(unsigned int& val);
    void setChannelsFirst(unsigned int& val);
    void setChannelsLast(unsigned int& val);
    UValDir rate();
    UValDir rateMin();
    UValDir rateMax();
    bool testRate(ValDir const& valdir);
    void setRate(ValDir const& valdir);
    void setRateMin(UValDir& valdir);
    void setRateMax(UValDir& valdir);
    void setRateMinmax(UValDir& min, UValDir& max);
    void setRateNear(UValDir& valdir);
    void setRateFirst(UValDir& valdir);
    void setRateLast(UValDir& valdir);
    void setRateResample(unsigned int val);
    unsigned int rateResample();
    void setExportBuffer(unsigned int val);
    unsigned int exportBuffer();
    void setPeriodWakeup(unsigned int val);
    unsigned int periodWakeup();
    void setDrainSilence(unsigned int val);
    unsigned int drainSilence();
    UValDir periodTime();
    UValDir periodTimeMin();
    UValDir periodTimeMax();
    bool testPeriodTime(ValDir const& valdir);
    void setPeriodTime(ValDir const& valdir);
    void setPeriodTimeMin(UValDir& valdir);
    void setPeriodTimeMax(UValDir& valdir);
    void setPeriodTimeMinmax(UValDir& min, UValDir& max);
    void setPeriodTimeNear(UValDir& valdir);
    void setPeriodTimeFirst(UValDir& valdir);
    void setPeriodTimeLast(UValDir& valdir);
    UFramesValDir periodSize();
    UFramesValDir periodSizeMin();
    UFramesValDir periodSizeMax();
    bool testPeriodSize(ValDir const& valdir);
    void setPeriodSize(ValDir const& valdir);
    void setPeriodSizeMin(UFramesValDir& valdir);
    void setPeriodSizeMax(UFramesValDir& valdir);
    void setPeriodSizeMinmax(UFramesValDir& min, UFramesValDir& max);
    void setPeriodSizeNear(UFramesValDir& valdir);
    void setPeriodSizeFirst(UFramesValDir& valdir);
    void setPeriodSizeLast(UFramesValDir& valdir);
    void setPeriodSizeInteger();
    UValDir periods();
    UValDir periodsMin();
    UValDir periodsMax();
    bool testPeriods(ValDir const& valdir);
    void setPeriods(ValDir const& valdir);
    void setPeriodsMin(UValDir& valdir);
    void setPeriodsMax(UValDir& valdir);
    void setPeriodsMinmax(UValDir& min, UValDir& max);
    void setPeriodsNear(UValDir& valdir);
    void setPeriodsFirst(UValDir& valdir);
    void setPeriodsLast(UValDir& valdir);
    void setPeriodsInteger();
    UValDir bufferTime();
    UValDir bufferTimeMin();
    UValDir bufferTimeMax();
    bool testBufferTime(ValDir const& valdir);
    void setBufferTime(ValDir const& valdir);
    void setBufferTimeMin(UValDir& valdir);
    void setBufferTimeMax(UValDir& valdir);
    void setBufferTimeMinmax(UValDir& min, UValDir& max);
    void setBufferTimeNear(UValDir& valdir);
    void setBufferTimeFirst(UValDir& valdir);
    void setBufferTimeLast(UValDir& valdir);
    UFrames bufferSize();
    UFrames bufferSizeMin();
    UFrames bufferSizeMax();
    bool testBufferSize(UFrames val);
    void setBufferSize(UFrames val);
    void setBufferSizeMin(UFrames& val);
    void setBufferSizeMax(UFrames& val);
    void setBufferSizeMinmax(UFrames& min, UFrames& max);
    void setBufferSizeNear(UFrames& val);
    void setBufferSizeFirst(UFrames& val);
    void setBufferSizeLast(UFrames& val);
    UFrames minAlign();
    std::string dump();
private:
    friend class Device;
    HWParams(Device&);
    Device& device_;
};

class SWParams : private _snd_pcm_sw_params {
public:
    SWParams(SWParams const& o);
    ~SWParams();

    static SWParams current(Device&);
    UFrames boundary();
    void setTstampMode(Tstamp val);
    Tstamp tstampMode();
    void setTstampType(TstampType val);
    TstampType tstampType();
    void setAvailMin(UFrames val);
    UFrames availMin();
    void setPeriodEvent(int val);
    int periodEvent();
    void setStartThreshold(UFrames val);
    UFrames startThreshold();
    void setStopThreshold(UFrames val);
    UFrames stopThreshold();
    void setSilenceThreshold(UFrames val);
    UFrames silenceThreshold();
    void setSilenceSize(UFrames val);
    UFrames silenceSize();
    std::string dump();
private:
    friend class Device;
    SWParams(Device&);
    Device& device_;
};

class Status : private _snd_pcm_status {
public:
    Status();
    Status(Status const& o);
    ~Status();

    State state() noexcept;
    ::timespec triggerTstamp() noexcept;
    ::timespec tstamp() noexcept;
    ::timespec audioTstamp() noexcept;
    ::timespec driverTstamp() noexcept;
    AudioTstampReport audioHtstampReport() noexcept;
    void setAudioHtstampConfig(AudioTstampConfig& audio_tstamp_config) noexcept;
    SFrames delay() noexcept;
    UFrames avail() noexcept;
    UFrames availMax() noexcept;
    UFrames overrange() noexcept;
    std::string dump();

private:
    friend class Device;
};

class Device
{
public:
    Device(char const* name, Stream stream, int mode);
    ~Device();

    std::string name();
    Type type() noexcept;
    Stream stream() noexcept;
    Info info();

    void apply(HWParams& params);
    void apply(SWParams& params);

    void prepare();
    void reset();

    Status status();
    
    void start();
    void drop();
    void drain();
    void pause(bool enable);

    State state() noexcept;

    static void link(Device& d1, Device& d2);
    void unlink();

    UFrames avail();
private:
    friend class HWParams;
    friend class SWParams;
    std::unique_ptr<struct _snd_pcm, int (*)(struct _snd_pcm*)> pcm_;
};

} // namespace pcm

namespace ctl
{

//=======================================================================
// forward declarations
class Control;

//=======================================================================
class CardInfo : private _snd_ctl_card_info {
public:
    CardInfo(CardInfo const& o);
    ~CardInfo();

    void clear() noexcept;
    int card();
    std::string id();
    std::string driver();
    std::string name();
    std::string longname();
    std::string mixername();
    std::string components();
private:
    friend class Control;
    CardInfo();
};

//=======================================================================
struct Cards 
{
    //=======================================================================
    class Iterator
    {
    public:
        //=======================================================================
        ~Iterator();

        //=======================================================================
        class Value
        {
        public:
            int index() noexcept;
            std::string name();
            std::string longname();

        private:
            int const idx__;
            friend class Iterator;
            Value(int);
        };

        class ValuePointer
        {
        public:
            Value* operator->();
        private:
            friend class Iterator;
            ValuePointer(int);
            Value value_;
        };

        //=======================================================================
        using value_type        = Value;
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::size_t;

        value_type operator*();
        ValuePointer operator->();
        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& b) const noexcept;
        bool operator!=(const Iterator& b) const noexcept;

    private:
        friend struct Cards;
        Iterator(int);
        int idx_;
    };

    //=======================================================================
    Iterator begin();
    Iterator end();
};

//=======================================================================
class Control : private _snd_ctl_card_info
{
public:
    Control(std::string const& name, int mode);
    ~Control();

    CardInfo info();
    void info(pcm::Info&);
    
    //=======================================================================
    class Devices 
    {
    public:
        class Iterator
        {
        public:
            //=======================================================================
            ~Iterator();

            //=======================================================================
            class ValuePointer
            {
            public:
                int* operator->();
            private:
                friend class Iterator;
                ValuePointer(int);
                int value_;
            };

            //=======================================================================
            using value_type        = int;
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::size_t;

            value_type operator*();
            ValuePointer operator->();
            Iterator& operator++();
            Iterator operator++(int);

            bool operator==(const Iterator& b) const noexcept;
            bool operator!=(const Iterator& b) const noexcept;

        private:
            friend class Control;
            friend class Devices;
            Iterator(Control*, int);
            Control* ctl_;
            int idx_;
        };

        //=======================================================================
        Iterator begin();
        Iterator end();
    private:
        Control& ctl__;
        friend class Control;
        Devices(Control&);
    };

    Devices devices();
private:
    friend class Devices::Iterator;
    friend class Devices::Iterator::ValuePointer;
    friend class Devices;
    std::unique_ptr<_snd_ctl, int (*)(_snd_ctl*)> ctl_;
};

} // namespace ctl
} // namespace alsa