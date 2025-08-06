#include "Sampler.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::shader
{
    Sampler::Sampler(ID3D11Device* const pDevice, const D3D11_SAMPLER_DESC& sDesc, const UINT& startSlot)
        :
        m_start_slot_(startSlot)
    {
        if (FAILED(pDevice->CreateSamplerState(&sDesc, &m_pSamplerState_)))
        {
            throw std::runtime_error("Could NOT create SamplerState!");
        }
    }


    void Sampler::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->PSSetSamplers(m_start_slot_, 1U, m_pSamplerState_.GetAddressOf());
    }
}

#endif
