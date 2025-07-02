#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    class DepthStencil
    {
    public:
        explicit DepthStencil(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc)
        {
            if (FAILED(pDevice->CreateDepthStencilView(tex2d.GetBuffer(), &dsvDesc, &m_pDSV_)))
            {
                throw std::runtime_error("Could NOT create DepthStencilView!");
            }
        }

        explicit DepthStencil()                        = default;
        explicit DepthStencil(const DepthStencil&)     = delete;
        explicit DepthStencil(DepthStencil&&) noexcept = delete;

        auto operator = (const DepthStencil&)     -> DepthStencil& = delete;
        auto operator = (DepthStencil&&) noexcept -> DepthStencil& = default;
        ~DepthStencil() noexcept                                   = default;


    public:
        auto GetView() const noexcept -> ID3D11DepthStencilView*
        {
            return m_pDSV_.Get();
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDSV_;


    private:
    };
}

#endif
