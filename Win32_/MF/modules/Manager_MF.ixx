module;

#ifdef FATLIB_BUILDING_WITH_MSVC
#include "../include/Manager.hpp"
#endif

export module FatPound.Win32.MF.Manager;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using mf::Manager;
}

#endif

// module : private;
