module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "WindowEx.hpp"
#endif

export module FatPound.Win32.WindowEx;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound
{
    using win32::WindowEx;
}

#endif

// module : private;
