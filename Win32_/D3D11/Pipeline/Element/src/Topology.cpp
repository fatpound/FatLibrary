#include <Win32_/D3D11/Pipeline/Element/include/Topology.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::d3d11::pipeline
{
    Topology::Topology(const D3D11_PRIMITIVE_TOPOLOGY& type) noexcept
        :
        m_type_(type)
    {

    }


    void Topology::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->IASetPrimitiveTopology(m_type_);
    }
}

#endif
