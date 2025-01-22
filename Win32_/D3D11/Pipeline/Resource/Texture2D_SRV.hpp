#pragma once

#include "../Bindable.hpp"

#include "Texture2D.hpp"

#include <Util/Surface.hpp>

namespace fatpound::win32::d3d11::pipeline::resource
{
    template <bool ForFramework>
	class Texture2D_SRV final : public Bindable, private Texture2D<ForFramework>
    {
    public:
        Texture2D_SRV(ID3D11Device* const pDevice, const UINT width, const UINT height, const UINT msaaCount, const UINT msaaQuality, std::shared_ptr<FATSPACE_UTIL::Surface> pSurface = {})
            :
            Texture2D(pDevice, width, height, msaaCount, msaaQuality, std::move(pSurface))
        {
            D3D11_TEXTURE2D_DESC tx2dDesc{};
            Texture2D::Get()->GetDesc(&tx2dDesc);

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
            srvDesc.Format = tx2dDesc.Format;
            srvDesc.Texture2D.MipLevels = tx2dDesc.MipLevels;

            if constexpr (ForFramework)
            {
                srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            }
            else
            {
                if (msaaCount == 1u)
                {
                    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                }
                else
                {
                    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
                }
            }
            
            const auto& hr = pDevice->CreateShaderResourceView(Texture2D::Get(), &srvDesc, &m_pSRV_);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
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