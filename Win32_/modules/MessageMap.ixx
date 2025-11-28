module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "MessageMap.hpp"
#endif

export module FatPound.Win32.MessageMap;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound
{
    using win32::MessageMap;
}

#endif

// module : private;
