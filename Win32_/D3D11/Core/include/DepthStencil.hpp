#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>

namespace fatpound::win32::d3d11::core
{
    class DepthStencil
    {
    public:
        explicit DepthStencil(ID3D11Device* const pDevice, const resource::Texture2D& tex2d, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);

        explicit DepthStencil()                        = default;
        explicit DepthStencil(const DepthStencil&)     = delete;
        explicit DepthStencil(DepthStencil&&) noexcept = delete;

        auto operator = (const DepthStencil&)     -> DepthStencil& = delete;
        auto operator = (DepthStencil&&) noexcept -> DepthStencil& = default;
        ~DepthStencil() noexcept                                   = default;


    public:
        auto GetView() const noexcept -> ID3D11DepthStencilView*;


    protected:
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDSV_;


    private:
    };
}

#endif
