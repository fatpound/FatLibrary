module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "IWindow.hpp"
#endif

export module FatPound.Win32.IWindow;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound
{
    using win32::IWindow;
    using win32::WndClassEx;
}

#endif

// module : private;
