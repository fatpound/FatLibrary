module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "../include/Graphics.hpp"
#endif

export module FatPound.Win32.D2D.Graphics;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using d2d::Graphics;
}

#endif

// module : private;
