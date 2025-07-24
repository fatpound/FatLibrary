#include "Viewport.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::d3d11::core
{
    Viewport::Viewport(const D3D11_VIEWPORT& vp) noexcept
        :
        m_vp_(vp)
    {

    }


    void Viewport::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->RSSetViewports(1U, &m_vp_);
    }
}

#endif
