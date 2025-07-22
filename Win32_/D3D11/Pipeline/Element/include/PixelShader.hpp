#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/include/Bindable.hpp>

#include <string>

namespace fatpound::win32::d3d11::pipeline
{
    class PixelShader : public Bindable
    {
    public:
        explicit PixelShader(ID3D11Device* const pDevice, const std::wstring& path);
        explicit PixelShader(ID3D11Device* const pDevice, const Microsoft::WRL::ComPtr<ID3DBlob>& pBlob);

        explicit PixelShader()                       = delete;
        explicit PixelShader(const PixelShader&)     = delete;
        explicit PixelShader(PixelShader&&) noexcept = delete;

        auto operator = (const PixelShader&)     -> PixelShader& = delete;
        auto operator = (PixelShader&&) noexcept -> PixelShader& = delete;
        virtual ~PixelShader() noexcept override                 = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11PixelShader>  m_pPixelShader_;


    private:
    };
}

#endif
