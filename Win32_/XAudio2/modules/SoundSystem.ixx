module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "SoundSystem.hpp"
#endif

export module FatPound.Win32.XAudio2.SoundSystem;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using xaudio2::SoundSystem;
}

#endif

// module : private;
