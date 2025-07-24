module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "../include/Common.hpp"
#endif

export module FatPound.Win32.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound
{
    using win32::ModuleHandleOf;
}

#endif

// module : private;
