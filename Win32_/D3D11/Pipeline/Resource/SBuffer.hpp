#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

#include "../Bindable.hpp"

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class SBuffer : public Bindable
    {
    public:
        explicit SBuffer(ID3D11Device* const pDevice, ID3D11DeviceContext* const pImmediateContext, const std::vector<T>& structures)
        {
            {
                const D3D11_BUFFER_DESC sbd
                {
                    .ByteWidth           = sizeof(T) * static_cast<UINT>(structures.size()),
                    .Usage               = D3D11_USAGE_DEFAULT,
                    .BindFlags           = D3D11_BIND_SHADER_RESOURCE,
                    .CPUAccessFlags      = 0U,
                    .MiscFlags           = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,
                    .StructureByteStride = sizeof(T)
                };

                const D3D11_SUBRESOURCE_DATA initData{ .pSysMem = structures.data() };

                if (const auto& hr = pDevice->CreateBuffer(&sbd, &initData, &m_pStructuredBuffer_); FAILED(hr))
                {
                    throw std::runtime_error("Could NOT Create Direct3D SBuffer in function: " __FUNCSIG__);
                }
            }

            {
                const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc
                {
                    .Format        = DXGI_FORMAT_UNKNOWN,
                    .ViewDimension = D3D11_SRV_DIMENSION_BUFFER,
                    .Buffer        = { .ElementWidth = static_cast<UINT>(structures.size()) }
                };

                if (const auto& hr = pDevice->CreateShaderResourceView(m_pStructuredBuffer_.Get(), &srvDesc, &m_pShaderResourceView_); FAILED(hr))
                {
                    throw std::runtime_error("Could NOT Create Direct3D ShaderResourceView in function: " __FUNCSIG__);
                }
            }

            pImmediateContext->VSSetShaderResources(0U, 1U, m_pShaderResourceView_.GetAddressOf());
        }

        explicit SBuffer()                   = delete;
        explicit SBuffer(const SBuffer&)     = delete;
        explicit SBuffer(SBuffer&&) noexcept = delete;

        auto operator = (const SBuffer&)     -> SBuffer& = delete;
        auto operator = (SBuffer&&) noexcept -> SBuffer& = delete;
        virtual ~SBuffer() noexcept override             = default;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView_{};
        ::Microsoft::WRL::ComPtr<ID3D11Buffer>             m_pStructuredBuffer_{};


    private:
    };
}

#endif
