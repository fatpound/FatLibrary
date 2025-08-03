module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "ResourcePack.hpp"
#endif

export module FatPound.Win32.D3D11.ResourcePack;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using d3d11::ResourcePack;
    using d3d11::FrameworkResourcePack;
}

#endif

// module : private;
