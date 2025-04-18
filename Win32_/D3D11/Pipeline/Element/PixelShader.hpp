#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatWin32.hpp>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

#include "../Bindable.hpp"

#include <string>
#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline::element
{
    class PixelShader final : public Bindable
    {
    public:
        explicit PixelShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            ::Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

            ::D3DReadFileToBlob(path.c_str(), &pBlob);

            if (const auto& hr = pDevice->CreatePixelShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pPixelShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D PixelShader in function: " __FUNCSIG__);
            }
        }

        explicit PixelShader()                       = delete;
        explicit PixelShader(const PixelShader&)     = delete;
        explicit PixelShader(PixelShader&&) noexcept = delete;

        auto operator = (const PixelShader&)     -> PixelShader& = delete;
        auto operator = (PixelShader&&) noexcept -> PixelShader& = delete;
        virtual ~PixelShader() noexcept override final           = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetShader(m_pPixelShader_.Get(), nullptr, 0U);
        }


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader_;


    private:
    };
}

#endif
