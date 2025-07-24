module;

#ifdef FATLIB_BUILDING_WITH_MSVC
#include "../include/Manager.hpp"
#endif

export module FatPound.Win32.GDI_Plus.Manager;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using gdi_plus::Manager;
}

#endif

// module : private;
