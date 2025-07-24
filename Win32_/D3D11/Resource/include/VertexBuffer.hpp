#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>

#include <array>
#include <vector>

namespace fatpound::win32::d3d11::resource
{
    class VertexBuffer : public Bindable
    {
    public:
        explicit VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const void* const pVerticesData);

        template <typename T, std::size_t N>
        explicit VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const std::array<T, N>& vertices)
            :
            VertexBuffer(pDevice, bufDesc, vertices.data())
        {

        }

        template <typename T>
        explicit VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const std::vector<T>& vertices)
            :
            VertexBuffer(pDevice, bufDesc, vertices.data())
        {

        }

        explicit VertexBuffer()                        = delete;
        explicit VertexBuffer(const VertexBuffer&)     = delete;
        explicit VertexBuffer(VertexBuffer&&) noexcept = delete;

        auto operator = (const VertexBuffer&)     -> VertexBuffer& = delete;
        auto operator = (VertexBuffer&&) noexcept -> VertexBuffer& = delete;
        virtual ~VertexBuffer() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer>   m_pVertexBuffer_;
        UINT                                   m_stride_;


    private:
    };
}

#endif
