#include <Win32_/D3D11/Pipeline/Resource/Texture2D.hpp>

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    Texture2D::Texture2D(IDXGISwapChain* const pSwapChain)
    {
        if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_pTex2d_)))
        {
            throw std::runtime_error("Could NOT get the buffer from SwapChain!");
        }
    }
    Texture2D::Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, std::shared_ptr<FATSPACE_UTILITY::Surface> pSurface)
    {
        if (pSurface not_eq nullptr)
        {
            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem = *pSurface,
                .SysMemPitch = pSurface->GetPitch<UINT>(),
                .SysMemSlicePitch = {}
            };

            if (FAILED(pDevice->CreateTexture2D(&tex2dDesc, &sd, &m_pTex2d_)))
            {
                throw std::runtime_error("Could NOT create Texture2D!");
            }
        }
        else
        {
            throw std::runtime_error("pSurface is empty!");
        }
    }
    Texture2D::Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc)
    {
        if (FAILED(pDevice->CreateTexture2D(&tex2dDesc, nullptr, &m_pTex2d_)))
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }
    }


    auto Texture2D::GetBuffer() const noexcept -> ID3D11Texture2D*
    {
        return m_pTex2d_.Get();
    }
}
