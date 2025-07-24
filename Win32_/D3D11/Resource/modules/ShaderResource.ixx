module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "ShaderResource.hpp"
#endif

export module FatPound.Win32.D3D11.Resource.ShaderResource;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32::d3d11
{
    using resource::ShaderResource;
}

#endif

// module : private;
