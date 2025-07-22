#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Resource/include/CBuffer.hpp>

namespace fatpound::win32::d3d11::pipeline
{
    template <typename T>
    class VertexCBuffer : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit VertexCBuffer()                         = delete;
        explicit VertexCBuffer(const VertexCBuffer&)     = delete;
        explicit VertexCBuffer(VertexCBuffer&&) noexcept = delete;

        auto operator = (const VertexCBuffer&)     -> VertexCBuffer& = delete;
        auto operator = (VertexCBuffer&&) noexcept -> VertexCBuffer& = delete;
        virtual ~VertexCBuffer() noexcept override                   = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->VSSetConstantBuffers(0U, 1U, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif
