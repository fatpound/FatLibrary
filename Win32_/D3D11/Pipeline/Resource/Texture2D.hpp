#pragma once

#include "../Bindable.hpp"

#include <Util/Surface.hpp>

#include <memory>

namespace fatpound::win32::d3d11::pipeline::resource
{
    class Texture2D final : public Bindable
    {
    public:
        Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, std::shared_ptr<FATSPACE_UTIL::Surface> pSurface = {})
        {
            ::Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;

            const D3D11_SUBRESOURCE_DATA* pSubresourceData{};

            if (pSurface not_eq nullptr)
            {
                D3D11_SUBRESOURCE_DATA sd{};
                sd.pSysMem = *pSurface;
                sd.SysMemPitch = pSurface->GetPitch<UINT>();

                pSubresourceData = &sd;
            }

            {
                const auto& hr = pDevice->CreateTexture2D(&tex2dDesc, pSubresourceData, &pTexture);

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create Texture2D!");
                }
            }

            {
                const auto& hr = pDevice->CreateShaderResourceView(pTexture.Get(), &srvDesc, &m_pSRV_);

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create ShaderResourceView!");
                }
            }
        }


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            pImmediateContext->PSSetShaderResources(0, 1, m_pSRV_.GetAddressOf());
        }


    protected:


    private:
        ::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV_;
    };
}