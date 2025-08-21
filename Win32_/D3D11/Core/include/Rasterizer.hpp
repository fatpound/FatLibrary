#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <Win32_/D3D11/include/Bindable.hpp>

namespace fatpound::win32::d3d11::core
{
    class Rasterizer : public Bindable
    {
    public:
        explicit Rasterizer(ID3D11Device* const pDevice, const D3D11_RASTERIZER_DESC& rDesc);

        explicit Rasterizer()                      = delete;
        explicit Rasterizer(const Rasterizer&)     = delete;
        explicit Rasterizer(Rasterizer&&) noexcept = default;

        auto operator = (const Rasterizer&)     -> Rasterizer& = delete;
        auto operator = (Rasterizer&&) noexcept -> Rasterizer& = default;
        virtual ~Rasterizer() noexcept override                = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11RasterizerState>  m_pRasterizerState_;


    private:
    };
}

#endif
