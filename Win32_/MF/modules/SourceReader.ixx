module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "SourceReader.hpp"
#endif

export module FatPound.Win32.MF.SourceReader;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using mf::SourceReader;
}

#endif

// module : private;
