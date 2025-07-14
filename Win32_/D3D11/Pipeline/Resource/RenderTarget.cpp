#include <Win32_/D3D11/Pipeline/Resource/RenderTarget.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    RenderTarget::RenderTarget(ID3D11Device* const pDevice, const Texture2D& tex2d)
    {
        if (FAILED(pDevice->CreateRenderTargetView(tex2d.GetBuffer(), nullptr, &m_pRTV_)))
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }
    }


    void RenderTarget::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->OMSetRenderTargets(1U, m_pRTV_.GetAddressOf(), nullptr);
    }

    auto RenderTarget::GetView() const noexcept -> ID3D11RenderTargetView*
    {
        return m_pRTV_.Get();
    }

    void RenderTarget::BindWithDepthStencilView(ID3D11DeviceContext* pImmediateContext, ID3D11DepthStencilView* const pDSV)
    {
        pImmediateContext->OMSetRenderTargets(1U, m_pRTV_.GetAddressOf(), pDSV);
    }
}

#endif
