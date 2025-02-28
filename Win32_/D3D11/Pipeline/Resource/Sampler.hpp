#pragma once

#include "../Bindable.hpp"

namespace fatpound::win32::d3d11::pipeline::resource
{
    class Sampler final : public Bindable
    {
    public:
        Sampler(ID3D11Device* const pDevice, const D3D11_SAMPLER_DESC& sDesc)
        {
            const auto& hr = pDevice->CreateSamplerState(&sDesc, &m_pSamplerState_);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT create SamplerState");
            }
        }


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetSamplers(0, 1, m_pSamplerState_.GetAddressOf());
        }


    protected:


    private:
        ::Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState_;
    };
}