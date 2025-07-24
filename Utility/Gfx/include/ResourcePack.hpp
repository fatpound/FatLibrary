#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/Namespaces.hpp>

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Utility/Gfx/include/SizePack.hpp>

#include <Utility/include/Surface.hpp>
#include <Win32_/D3D11/Core/include/RenderTarget.hpp>
#include <Win32_/D3D11/Core/include/DepthStencil.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>

namespace fatpound::utility::gfx
{
    struct ResourcePack
    {
        explicit ResourcePack() noexcept               = default;
        explicit ResourcePack(const ResourcePack&)     = delete;
        explicit ResourcePack(ResourcePack&&) noexcept = delete;

        auto operator = (const ResourcePack&)     -> ResourcePack& = delete;
        auto operator = (ResourcePack&&) noexcept -> ResourcePack& = delete;
        ~ResourcePack() noexcept                                   = default;

        Microsoft::WRL::ComPtr<IDXGISwapChain>        m_pSwapChain;
        Microsoft::WRL::ComPtr<ID3D11Device>          m_pDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>   m_pImmediateContext;
        win32::d3d11::core::RenderTarget              m_render_target;
        win32::d3d11::core::DepthStencil              m_depth_stencil;
    };

    struct FrameworkResourcePack final : public ResourcePack
    {
        win32::d3d11::resource::Texture2D             m_sysbufferTex2d;
        D3D11_MAPPED_SUBRESOURCE                      m_mappedSysbufferTex2d{};
        Surface                                       m_surface;

        explicit FrameworkResourcePack(const SizePack& dimensions);

        explicit FrameworkResourcePack() noexcept                        = default;
        explicit FrameworkResourcePack(const FrameworkResourcePack&)     = delete;
        explicit FrameworkResourcePack(FrameworkResourcePack&&) noexcept = delete;

        auto operator = (const FrameworkResourcePack&)     -> FrameworkResourcePack& = delete;
        auto operator = (FrameworkResourcePack&&) noexcept -> FrameworkResourcePack& = delete;
        ~FrameworkResourcePack() noexcept                                            = default;
    };
}

#endif
