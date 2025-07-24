module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "../include/Graphics.hpp"
#endif

export module FatPound.Win32.D3D11.Graphics;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using d3d11::Graphics;
}

#endif

// module : private;
