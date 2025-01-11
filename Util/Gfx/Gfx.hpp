#pragma once

#include <FatWin32.hpp>

#include "FullScreenQuad.hpp"
#include "ResourcePack.hpp"

#include <d3d11.h>

#include <wrl.h>

namespace fatpound::util::gfx
{
    auto GetDXGIFactory(ID3D11Device* const pDevice) -> ::Microsoft::WRL::ComPtr<IDXGIFactory>;

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND hWnd, UINT& flag);
}