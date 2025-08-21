#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/Namespaces.hpp>

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Utility/include/SizePack.hpp>
#include <Utility/include/Surface.hpp>
#include <Win32_/D3D11/Core/include/RenderTarget.hpp>
#include <Win32_/D3D11/Core/include/DepthStencil.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>

namespace fatpound::win32::d3d11::details_rp
{
    struct ResourcePackBase
    {
        explicit ResourcePackBase() noexcept = default;
        explicit ResourcePackBase(const ResourcePackBase&) = delete;
        explicit ResourcePackBase(ResourcePackBase&&) noexcept = delete;

        auto operator = (const ResourcePackBase&)     -> ResourcePackBase & = delete;
        auto operator = (ResourcePackBase&&) noexcept -> ResourcePackBase & = delete;
        ~ResourcePackBase() noexcept = default;

        Microsoft::WRL::ComPtr<IDXGISwapChain>        m_pSwapChain;
        Microsoft::WRL::ComPtr<ID3D11Device>          m_pDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>   m_pImmediateContext;
        win32::d3d11::core::RenderTarget              m_render_target;
    };
}

namespace fatpound::win32::d3d11
{
    struct ResourcePack : public details_rp::ResourcePackBase
    {
        explicit ResourcePack() noexcept               = default;
        explicit ResourcePack(const ResourcePack&)     = delete;
        explicit ResourcePack(ResourcePack&&) noexcept = delete;

        auto operator = (const ResourcePack&)     -> ResourcePack& = delete;
        auto operator = (ResourcePack&&) noexcept -> ResourcePack& = delete;
        ~ResourcePack() noexcept                                   = default;
    };

    struct FrameworkResourcePack : public details_rp::ResourcePackBase
    {
        explicit FrameworkResourcePack(const utility::SizePack& dimensions);

        explicit FrameworkResourcePack() noexcept                        = default;
        explicit FrameworkResourcePack(const FrameworkResourcePack&)     = delete;
        explicit FrameworkResourcePack(FrameworkResourcePack&&) noexcept = delete;

        auto operator = (const FrameworkResourcePack&)     -> FrameworkResourcePack& = delete;
        auto operator = (FrameworkResourcePack&&) noexcept -> FrameworkResourcePack& = delete;
        ~FrameworkResourcePack() noexcept                                            = default;

        win32::d3d11::resource::Texture2D   m_sysbufferTex2d;
        D3D11_MAPPED_SUBRESOURCE            m_mappedSysbufferTex2d{};
        utility::Surface                    m_surface;
    };
}

#endif
