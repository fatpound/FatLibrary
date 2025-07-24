module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "PixelShader.hpp"
#endif

export module FatPound.Win32.D3D11.Shader.PixelShader;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32::d3d11
{
    using shader::PixelShader;
}

#endif

// module : private;
