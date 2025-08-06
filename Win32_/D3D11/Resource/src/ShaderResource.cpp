#include "ShaderResource.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::resource
{
    ShaderResource::ShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot)
        :
        m_start_slot_(startSlot)
    {
        if (FAILED(pDevice->CreateShaderResourceView(tex2d.GetBuffer(), &srvDesc, &m_pSRV_)))
        {
            throw std::runtime_error("Could NOT create ShaderResourceView!");
        }
    }


    void ShaderResource::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->PSSetShaderResources(m_start_slot_, 1U, m_pSRV_.GetAddressOf());
    }

    auto ShaderResource::GetView() const noexcept -> ID3D11ShaderResourceView*
    {
        return m_pSRV_.Get();
    }
}

#endif
