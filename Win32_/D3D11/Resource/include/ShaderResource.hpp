#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

namespace fatpound::win32::d3d11::resource
{
    class ShaderResource
    {
    public:
        explicit ShaderResource(ID3D11Device* const pDevice, ID3D11Resource* const d3dres, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U);

        explicit ShaderResource()                          = delete;
        explicit ShaderResource(const ShaderResource&)     = delete;
        explicit ShaderResource(ShaderResource&&) noexcept = default;

        auto operator = (const ShaderResource&)     -> ShaderResource& = delete;
        auto operator = (ShaderResource&&) noexcept -> ShaderResource& = default;
        ~ShaderResource() noexcept                                     = default;


    public:
        auto GetView()          const noexcept -> ID3D11ShaderResourceView*;
        auto GetAddressOfView() const noexcept -> ID3D11ShaderResourceView* const*;

        auto GetStartSlot() const noexcept -> UINT;


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>   m_pSRV_;
        UINT                                               m_start_slot_{};


    private:
    };
}

#endif
