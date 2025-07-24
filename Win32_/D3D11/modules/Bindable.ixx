module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "Bindable.hpp"
#endif

export module FatPound.Win32.D3D11.Bindable;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using d3d11::Bindable;
}

#endif

// module : private;
