#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/Resource/include/SBuffer.hpp>

namespace fatpound::win32::d3d11::resource
{
    template <typename T>
    class PixelSBuffer : public SBuffer<T>
    {
        using SBuffer<T>::SBuffer;

    public:
        explicit PixelSBuffer()                        = delete;
        explicit PixelSBuffer(const PixelSBuffer&)     = delete;
        explicit PixelSBuffer(PixelSBuffer&&) noexcept = default;

        auto operator = (const PixelSBuffer&)     -> PixelSBuffer& = delete;
        auto operator = (PixelSBuffer&&) noexcept -> PixelSBuffer& = default;
        virtual ~PixelSBuffer() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetShaderResources(this->m_pVShaderResource_->GetStartSlot(), 1U, this->m_pVShaderResource_->GetAddressOfView());
        }


    protected:


    private:
    };
}

#endif
