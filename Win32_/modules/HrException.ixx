module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "HrException.hpp"
#endif

export module FatPound.Win32.HrException;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound
{
    using win32::HrException;
}

#endif

// module : private;
