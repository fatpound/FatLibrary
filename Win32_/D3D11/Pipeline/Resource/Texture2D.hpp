#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

#include <Utility/Surface.hpp>

#include <memory>
#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    class Texture2D
    {
    public:
        explicit Texture2D(IDXGISwapChain* const pSwapChain)
        {
            if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_pTex2d_)))
            {
                throw std::runtime_error("Could NOT get the buffer from SwapChain!");
            }
        }
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, std::shared_ptr<FATSPACE_UTILITY::Surface> pSurface)
        {
            if (pSurface not_eq nullptr)
            {
                const D3D11_SUBRESOURCE_DATA sd
                {
                    .pSysMem          = *pSurface,
                    .SysMemPitch      =  pSurface->GetPitch<UINT>(),
                    .SysMemSlicePitch = {}
                };

                if (FAILED(pDevice->CreateTexture2D(&tex2dDesc, &sd, &m_pTex2d_)))
                {
                    throw std::runtime_error("Could NOT create Texture2D!");
                }
            }
            else
            {
                throw std::runtime_error("pSurface is empty!");
            }
        }
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc)
        {
            if (FAILED(pDevice->CreateTexture2D(&tex2dDesc, nullptr, &m_pTex2d_)))
            {
                throw std::runtime_error("Could NOT create Texture2D!");
            }
        }

        explicit Texture2D()                     = default;
        explicit Texture2D(const Texture2D&)     = delete;
        explicit Texture2D(Texture2D&&) noexcept = delete;

        auto operator = (const Texture2D&)     -> Texture2D& = delete;
        auto operator = (Texture2D&&) noexcept -> Texture2D& = default;
        ~Texture2D() noexcept                                = default;


    public:
        auto GetBuffer() const noexcept -> ID3D11Texture2D*
        {
            return m_pTex2d_.Get();
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11Texture2D>  m_pTex2d_;


    private:
    };
}

#endif
