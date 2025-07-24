module;

#ifdef FATLIB_BUILDING_WITH_MSVC
#include "../include/Manager.hpp"
#endif

export module FatPound.Win32.COM.Manager;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using com::Manager;
}

#endif

// module : private;
