#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

namespace fatpound::win32::d3d11::pipeline
{
    class Sampler : public Bindable
    {
    public:
        explicit Sampler(ID3D11Device* const pDevice, const D3D11_SAMPLER_DESC& sDesc)
        {
            if (FAILED(pDevice->CreateSamplerState(&sDesc, &m_pSamplerState_)))
            {
                throw std::runtime_error("Could NOT create SamplerState!");
            }
        }

        explicit Sampler()                   = delete;
        explicit Sampler(const Sampler&)     = delete;
        explicit Sampler(Sampler&&) noexcept = delete;

        auto operator = (const Sampler&)     -> Sampler& = delete;
        auto operator = (Sampler&&) noexcept -> Sampler& = delete;
        virtual ~Sampler() noexcept override             = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetSamplers(0U, 1U, m_pSamplerState_.GetAddressOf());
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11SamplerState>  m_pSamplerState_;


    private:
    };
}

#endif
