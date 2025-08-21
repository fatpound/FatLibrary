module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "../include/Common.hpp"
#endif

export module FatPound.Win32.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

export import FatPound.Win32.Core;

export namespace fatpound
{
    using win32::ModuleHandleOf;
}

#endif

// module : private;
