#include <Win32_/D3D11/Pipeline/Element/include/VertexBuffer.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    VertexBuffer::VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const void* const pVerticesData)
        :
        m_stride_(bufDesc.StructureByteStride) // same as sizeof(T)
    {
        const D3D11_SUBRESOURCE_DATA sd
        {
            .pSysMem = pVerticesData,
            .SysMemPitch = {},
            .SysMemSlicePitch = {}
        };

        if (FAILED(pDevice->CreateBuffer(&bufDesc, &sd, &m_pVertexBuffer_)))
        {
            throw std::runtime_error("Could NOT create VertexBuffer!");
        }
    }


    void VertexBuffer::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        constexpr UINT offset{};

        pImmediateContext->IASetVertexBuffers(0U, 1U, m_pVertexBuffer_.GetAddressOf(), &m_stride_, &offset);
    }
}

#endif
