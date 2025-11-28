#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>
#include <Win32_/D3D11/Resource/include/ShaderResource.hpp>

namespace fatpound::win32::d3d11::resource
{
    class PixelShaderResource : public Bindable, public ShaderResource
    {
    public:
        explicit PixelShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U);

        explicit PixelShaderResource()                               = delete;
        explicit PixelShaderResource(const PixelShaderResource&)     = delete;
        explicit PixelShaderResource(PixelShaderResource&&) noexcept = default;

        auto operator = (const PixelShaderResource&)     -> PixelShaderResource& = delete;
        auto operator = (PixelShaderResource&&) noexcept -> PixelShaderResource& = default;
        virtual ~PixelShaderResource() noexcept override                         = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override;


    protected:


    private:
    };
}

#endif
