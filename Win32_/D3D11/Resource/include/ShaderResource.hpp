#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>

namespace fatpound::win32::d3d11::resource
{
    class ShaderResource : public Bindable
    {
    public:
        explicit ShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U);

        explicit ShaderResource()                          = delete;
        explicit ShaderResource(const ShaderResource&)     = delete;
        explicit ShaderResource(ShaderResource&&) noexcept = default;

        auto operator = (const ShaderResource&)     -> ShaderResource& = delete;
        auto operator = (ShaderResource&&) noexcept -> ShaderResource& = default;
        virtual ~ShaderResource() noexcept override                    = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override;


    public:
        auto GetView() const noexcept -> ID3D11ShaderResourceView*;


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>   m_pSRV_;
        UINT                                               m_start_slot_{};


    private:
    };
}

#endif
