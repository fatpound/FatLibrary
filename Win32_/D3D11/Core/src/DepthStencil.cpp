#include "DepthStencil.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::core
{
    DepthStencil::DepthStencil(ID3D11Device* const pDevice, const resource::Texture2D& tex2d, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc)
    {
        if (FAILED(pDevice->CreateDepthStencilView(tex2d.GetBuffer(), &dsvDesc, &m_pDSV_)))
        {
            throw std::runtime_error("Could NOT create DepthStencilView!");
        }
    }


    auto DepthStencil::GetView() const noexcept -> ID3D11DepthStencilView*
    {
        return m_pDSV_.Get();
    }
}

#endif
