module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "../include/Common.hpp"
#endif

export module FatPound.Win32.DXGI.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::win32
{
    using dxgi::GetFactoryFromDevice;
    using dxgi::ToggleAltEnterMode;
}

#endif

// module : private;
