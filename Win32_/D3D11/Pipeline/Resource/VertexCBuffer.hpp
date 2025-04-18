#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

#include "CBuffer.hpp"

namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class VertexCBuffer final : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit VertexCBuffer()                         = delete;
        explicit VertexCBuffer(const VertexCBuffer&)     = delete;
        explicit VertexCBuffer(VertexCBuffer&&) noexcept = delete;

        auto operator = (const VertexCBuffer&)     -> VertexCBuffer& = delete;
        auto operator = (VertexCBuffer&&) noexcept -> VertexCBuffer& = delete;
        virtual ~VertexCBuffer() noexcept override final             = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->VSSetConstantBuffers(0U, 1U, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif
