#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

namespace fatpound::win32::dxgi
{
    auto GetFactoryFromDevice(ID3D11Device* const pDevice) -> Microsoft::WRL::ComPtr<IDXGIFactory>;

    void ToggleAltEnterMode(ID3D11Device* const pDevice, const HWND& hWnd, UINT& flag);
}

#endif