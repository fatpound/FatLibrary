#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/include/Bindable.hpp>
#include <Win32_/D3D11/Pipeline/Resource/include/Texture2D.hpp>

namespace fatpound::win32::d3d11::pipeline
{
    class ShaderResource : public Bindable
    {
    public:
        explicit ShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc);

        explicit ShaderResource()                          = delete;
        explicit ShaderResource(const ShaderResource&)     = delete;
        explicit ShaderResource(ShaderResource&&) noexcept = delete;

        auto operator = (const ShaderResource&)     -> ShaderResource& = delete;
        auto operator = (ShaderResource&&) noexcept -> ShaderResource& = delete;
        virtual ~ShaderResource() noexcept override                    = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override;


    public:
        auto GetView() const noexcept -> ID3D11ShaderResourceView*;


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  m_pSRV_;


    private:
    };
}

#endif
