#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Resource/include/VertexShaderResource.hpp>

#include <vector>
#include <memory>
#include <stdexcept>

namespace fatpound::win32::d3d11::resource
{
    template <typename T>
    class SBuffer : public Bindable
    {
    public:
        explicit SBuffer(ID3D11Device* const pDevice, ID3D11DeviceContext* const pImmediateContext, const D3D11_BUFFER_DESC& bufDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const std::vector<T>& structures)
        {
            {
                const D3D11_SUBRESOURCE_DATA initData
                {
                    .pSysMem          = structures.data(),
                    .SysMemPitch      = {},
                    .SysMemSlicePitch = {}
                };

                if (FAILED(pDevice->CreateBuffer(&bufDesc, &initData, &m_pBuffer_)))
                {
                    throw std::runtime_error("Could NOT create SBuffer!");
                }
            }

            m_pVShaderResource_ = std::make_unique<VertexShaderResource>(pDevice, m_pBuffer_.Get(), srvDesc);

            m_pVShaderResource_->Bind(pImmediateContext);
        }

        explicit SBuffer()                   = delete;
        explicit SBuffer(const SBuffer&)     = delete;
        explicit SBuffer(SBuffer&&) noexcept = default;

        auto operator = (const SBuffer&)     -> SBuffer& = delete;
        auto operator = (SBuffer&&) noexcept -> SBuffer& = default;
        virtual ~SBuffer() noexcept override             = default;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer>    m_pBuffer_;
        std::unique_ptr<VertexShaderResource>   m_pVShaderResource_;


    private:
    };
}

#endif
