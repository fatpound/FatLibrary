#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

#include <vector>
#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    class IndexBuffer : public Bindable
    {
    public:
        template <std::integral T>
        explicit IndexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const DXGI_FORMAT& format, const std::vector<T>& indices)
            :
            m_format_(format),
            m_count_(static_cast<UINT>(indices.size()))
        {
            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem          = indices.data(),
                .SysMemPitch      = {},
                .SysMemSlicePitch = {}
            };

            if (FAILED(pDevice->CreateBuffer(&bufDesc, &sd, &m_pIndexBuffer_)))
            {
                throw std::runtime_error("Could NOT create IndexBuffer!");
            }
        }

        explicit IndexBuffer()                       = delete;
        explicit IndexBuffer(const IndexBuffer&)     = delete;
        explicit IndexBuffer(IndexBuffer&&) noexcept = delete;

        auto operator = (const IndexBuffer&)     -> IndexBuffer& = delete;
        auto operator = (IndexBuffer&&) noexcept -> IndexBuffer& = delete;
        virtual ~IndexBuffer() noexcept override                 = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override;


    public:
        auto GetFormat () const noexcept -> DXGI_FORMAT;
        auto GetCount  () const noexcept -> UINT;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer>   m_pIndexBuffer_;

        DXGI_FORMAT                            m_format_;

        UINT                                   m_count_;


    private:
    };
}

#endif
