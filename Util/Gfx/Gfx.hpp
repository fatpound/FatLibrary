#pragma once

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

#include "FullScreenQuad.hpp"
#include "ResourcePack.hpp"
#include "SizePack.hpp"

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)

namespace fatpound::util::gfx
{
    auto GetDXGIFactory(ID3D11Device* const pDevice) -> ::Microsoft::WRL::ComPtr<IDXGIFactory>;

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND hWnd, UINT& flag);
}

#endif
