#include <Win32_/D3D11/Pipeline/Element/IndexBuffer.hpp>

namespace fatpound::win32::d3d11::pipeline
{
    void IndexBuffer::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->IASetIndexBuffer(m_pIndexBuffer_.Get(), GetFormat(), 0U);
    }

    auto IndexBuffer::GetFormat() const noexcept -> DXGI_FORMAT
    {
        return m_format_;
    }
    auto IndexBuffer::GetCount() const noexcept -> UINT
    {
        return m_count_;
    }
}
