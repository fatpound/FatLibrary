#include <Win32_/D3D11/Pipeline/Element/PixelShader.hpp>

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    PixelShader::PixelShader(ID3D11Device* const pDevice, const std::wstring& path)
    {
        Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

        if (FAILED(::D3DReadFileToBlob(path.c_str(), &pBlob)))
        {
            throw std::runtime_error("CANNOT read Pixel Shader to D3D Blob!");
        }

        if (FAILED(pDevice->CreatePixelShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &m_pPixelShader_)))
        {
            throw std::runtime_error("Could NOT create PixelShader!");
        }
    }
    PixelShader::PixelShader(ID3D11Device* const pDevice, const Microsoft::WRL::ComPtr<ID3DBlob>& pBlob)
    {
        if (FAILED(pDevice->CreatePixelShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &m_pPixelShader_)))
        {
            throw std::runtime_error("Could NOT create PixelShader!");
        }
    }


    void PixelShader::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->PSSetShader(m_pPixelShader_.Get(), nullptr, 0U);
    }
}
