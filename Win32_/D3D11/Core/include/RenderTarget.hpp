#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Core/include/DepthStencil.hpp>
#include <Win32_/D3D11/Resource/include/Texture2D.hpp>

#include <optional>

namespace fatpound::win32::d3d11::core
{
    class RenderTarget : public Bindable
    {
    public:
        explicit RenderTarget(ID3D11Device* const pDevice, const resource::Texture2D& tex2d);
        explicit RenderTarget(
            ID3D11Device* const pDevice,
            const resource::Texture2D& rtvTex2d,
            const resource::Texture2D& dsvTex2d,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);

        explicit RenderTarget()                        = default;
        explicit RenderTarget(const RenderTarget&)     = delete;
        explicit RenderTarget(RenderTarget&&) noexcept = default;

        auto operator = (const RenderTarget&)     -> RenderTarget& = delete;
        auto operator = (RenderTarget&&) noexcept -> RenderTarget& = default;
        virtual ~RenderTarget() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override;


    public:
        auto GetView   () const noexcept -> ID3D11RenderTargetView*;
        auto GetDSView () const noexcept -> ID3D11DepthStencilView*;

        auto HasDepthStencil () const noexcept -> bool;


    protected:
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>   m_pRTV_;
        std::optional<DepthStencil>                      m_depth_stencil_;


    private:
    };
}

#endif
