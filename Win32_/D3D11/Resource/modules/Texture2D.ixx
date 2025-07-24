module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "Texture2D.hpp"
#endif

export module FatPound.Win32.D3D11.Resource.Texture2D;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32::d3d11
{
    using resource::Texture2D;
}

#endif

// module : private;
