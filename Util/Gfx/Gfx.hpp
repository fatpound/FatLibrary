#pragma once

#if FAT_BUILD_ONLY_WITH_MSVC
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

#include "FullScreenQuad.hpp"
#include "ResourcePack.hpp"
#include "SizePack.hpp"

#if FAT_BUILD_ONLY_WITH_MSVC

namespace fatpound::util::gfx
{
    auto GetDXGIFactory(ID3D11Device* const pDevice) -> ::Microsoft::WRL::ComPtr<IDXGIFactory>;

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND hWnd, UINT& flag);
}

#endif
