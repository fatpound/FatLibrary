#include "VertexShaderResource.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::d3d11::resource
{
    VertexShaderResource::VertexShaderResource(ID3D11Device* const pDevice, ID3D11Buffer* const d3dbuf, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot)
        :
        ShaderResource(pDevice, d3dbuf, srvDesc, startSlot)
    {

    }

    
    void VertexShaderResource::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->VSSetShaderResources(m_start_slot_, 1U, m_pSRV_.GetAddressOf());
    }
}

#endif
