#include "PixelShaderResource.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::d3d11::resource
{
    PixelShaderResource::PixelShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot)
        :
        ShaderResource(pDevice, tex2d.GetBuffer(), srvDesc, startSlot)
    {

    }

    
    void PixelShaderResource::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->PSSetShaderResources(m_start_slot_, 1U, m_pSRV_.GetAddressOf());
    }
}

#endif
