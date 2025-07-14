#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Resource/include/SBuffer.hpp>

namespace fatpound::win32::d3d11::pipeline
{
    template <typename T>
    class PixelSBuffer : public SBuffer<T>
    {
        using SBuffer<T>::SBuffer;

    public:
        explicit PixelSBuffer()                        = delete;
        explicit PixelSBuffer(const PixelSBuffer&)     = delete;
        explicit PixelSBuffer(PixelSBuffer&&) noexcept = delete;

        auto operator = (const PixelSBuffer&)     -> PixelSBuffer& = delete;
        auto operator = (PixelSBuffer&&) noexcept -> PixelSBuffer& = delete;
        virtual ~PixelSBuffer() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetShaderResources(0U, 1U, this->m_pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif
