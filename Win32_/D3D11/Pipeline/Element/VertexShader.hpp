#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

#include <string>
#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    class VertexShader final : public Bindable
    {
    public:
        explicit VertexShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

            if (FAILED(::D3DReadFileToBlob(path.c_str(), &pBlob)))
            {
                throw std::runtime_error("CANNOT read Vertex Shader to D3D Blob!");
            }

            if (const auto& hr = pDevice->CreateVertexShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pVertexShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create VertexShader!");
            }
        }
        explicit VertexShader(ID3D11Device* const pDevice, const Microsoft::WRL::ComPtr<ID3DBlob>& pBlob)
        {
            if (const auto& hr = pDevice->CreateVertexShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pVertexShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create VertexShader!");
            }
        }

        explicit VertexShader()                        = delete;
        explicit VertexShader(const VertexShader&)     = delete;
        explicit VertexShader(VertexShader&&) noexcept = delete;

        auto operator = (const VertexShader&)     -> VertexShader& = delete;
        auto operator = (VertexShader&&) noexcept -> VertexShader& = delete;
        virtual ~VertexShader() noexcept override final            = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->VSSetShader(m_pVertexShader_.Get(), nullptr, 0U);
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11VertexShader>  m_pVertexShader_;


    private:
    };
}

#endif
