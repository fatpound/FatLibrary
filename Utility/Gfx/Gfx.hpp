#pragma once

#if FAT_BUILDING_WITH_MSVC
    #include <FatWin32.hpp>
    #include <d3d11.h>
    #include <wrl.h>
#endif

#include "FullScreenQuad.hpp"
#include "ResourcePack.hpp"
#include "SizePack.hpp"

#if FAT_BUILDING_WITH_MSVC

namespace fatpound::utility::gfx
{
    static auto GetDXGIFactory(ID3D11Device* const pDevice) -> Microsoft::WRL::ComPtr<IDXGIFactory>
    {
        auto pDXGIDevice = Microsoft::WRL::ComPtr<IDXGIDevice>{};
        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        auto pDXGIAdapter = Microsoft::WRL::ComPtr<IDXGIAdapter>{};
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        auto pDXGIFactory = Microsoft::WRL::ComPtr<IDXGIFactory>{};
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        return pDXGIFactory;
    }

    static void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND& hWnd, UINT& flag)
    {
        static constexpr auto magicVal = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

        if ((flag bitand magicVal) not_eq 0U)
        {
            flag and_eq (compl magicVal);
        }
        else
        {
            flag or_eq magicVal;
        }

        GetDXGIFactory(pDevice)->MakeWindowAssociation(hWnd, flag);
    }
}

#endif
