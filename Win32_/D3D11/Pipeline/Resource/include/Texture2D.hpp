#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/include/Bindable.hpp>

#include <Utility/include/Surface.hpp>

#include <memory>

namespace fatpound::win32::d3d11::pipeline
{
    class Texture2D
    {
    public:
        explicit Texture2D(IDXGISwapChain* const pSwapChain);
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, std::shared_ptr<FATSPACE_UTILITY::Surface> pSurface);
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc);

        explicit Texture2D()                     = default;
        explicit Texture2D(const Texture2D&)     = delete;
        explicit Texture2D(Texture2D&&) noexcept = delete;

        auto operator = (const Texture2D&)     -> Texture2D& = delete;
        auto operator = (Texture2D&&) noexcept -> Texture2D& = default;
        ~Texture2D() noexcept                                = default;


    public:
        auto GetBuffer() const noexcept -> ID3D11Texture2D*;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Texture2D>  m_pTex2d_;


    private:
    };
}

#endif
