#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/Namespaces.hpp>

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>
#include <Win32_/D3D11/Resource/include/ShaderResource.hpp>

namespace fatpound::win32::d3d11::resource
{
    class VertexShaderResource : public Bindable, public ShaderResource
    {
    public:
        explicit VertexShaderResource(ID3D11Device* const pDevice, ID3D11Buffer* const d3dbuf, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U);

        explicit VertexShaderResource()                                = delete;
        explicit VertexShaderResource(const VertexShaderResource&)     = delete;
        explicit VertexShaderResource(VertexShaderResource&&) noexcept = default;

        auto operator = (const VertexShaderResource&)     -> VertexShaderResource& = delete;
        auto operator = (VertexShaderResource&&) noexcept -> VertexShaderResource& = default;
        virtual ~VertexShaderResource() noexcept override                          = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override;


    protected:


    private:
    };
}

#endif
