#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    // This is inteded for use as a base class, not an actual bindable
    //
    template <typename T>
    class CBuffer : public Bindable
    {
    public:
        explicit CBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const T& consts)
        {
            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem          = &consts,
                .SysMemPitch      = {},
                .SysMemSlicePitch = {}
            };

            if (const auto& hr = pDevice->CreateBuffer(&bufDesc, &sd, &m_pConstantBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create CBuffer!");
            }
        }
        explicit CBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc)
        {
            if (const auto& hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pConstantBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create CBuffer!");
            }
        }

        explicit CBuffer()                   = delete;
        explicit CBuffer(const CBuffer&)     = delete;
        explicit CBuffer(CBuffer&&) noexcept = delete;

        auto operator = (const CBuffer&)     -> CBuffer& = delete;
        auto operator = (CBuffer&&) noexcept -> CBuffer& = delete;
        virtual ~CBuffer() noexcept override             = default;


    public:
        virtual void Update(ID3D11DeviceContext* const pImmediateContext, const T& consts) final
        {
            D3D11_MAPPED_SUBRESOURCE msr;

            pImmediateContext->Map(
                m_pConstantBuffer_.Get(),
                0U,
                D3D11_MAP_WRITE_DISCARD,
                0U,
                &msr
            );

            std::memcpy(msr.pData, &consts, sizeof(consts));

            pImmediateContext->Unmap(m_pConstantBuffer_.Get(), 0U);
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer>  m_pConstantBuffer_;


    private:
    };
}

#endif
