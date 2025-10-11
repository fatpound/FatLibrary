#include "ShaderResource.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::resource
{
    ShaderResource::ShaderResource(ID3D11Device* const pDevice, ID3D11Resource* const d3dres, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot)
        :
        m_start_slot_(startSlot)
    {
        if (FAILED(pDevice->CreateShaderResourceView(d3dres, &srvDesc, &m_pSRV_)))
        {
            throw std::runtime_error("Could NOT create ShaderResourceView!");
        }
    }

    
    auto ShaderResource::GetView()          const noexcept -> ID3D11ShaderResourceView*
    {
        return m_pSRV_.Get();
    }
    auto ShaderResource::GetAddressOfView() const noexcept -> ID3D11ShaderResourceView* const*
    {
        return m_pSRV_.GetAddressOf();
    }

    auto ShaderResource::GetStartSlot() const noexcept -> UINT
    {
        return m_start_slot_;
    }
}

#endif
