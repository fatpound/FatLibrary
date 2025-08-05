#include "RenderTarget.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::core
{
    RenderTarget::RenderTarget(ID3D11Device* const pDevice, const resource::Texture2D& tex2d)
    {
        if (FAILED(pDevice->CreateRenderTargetView(tex2d.GetBuffer(), nullptr, &m_pRTV_)))
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }
    }
    RenderTarget::RenderTarget(ID3D11Device* const pDevice, const resource::Texture2D& tex2d, const DepthStencil& ds)
        :
        RenderTarget(pDevice, tex2d)
    {
        m_pDepthStencil_ = &ds;
    }

    void RenderTarget::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->OMSetRenderTargets(
            1U,
            m_pRTV_.GetAddressOf(),
            GetDSView()
        );
    }

    auto RenderTarget::GetView   () const noexcept -> ID3D11RenderTargetView*
    {
        return m_pRTV_.Get();
    }
    auto RenderTarget::GetDSView () const noexcept -> ID3D11DepthStencilView*
    {
        return m_pDepthStencil_ not_eq nullptr ? m_pDepthStencil_->GetView() : nullptr;
    }

    auto RenderTarget::HasDepthStencil () const noexcept-> bool
    {
        return m_pDepthStencil_ not_eq nullptr;
    }
}

#endif
