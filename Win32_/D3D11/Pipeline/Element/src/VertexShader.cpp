#include <Win32_/D3D11/Pipeline/Element/include/VertexShader.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    VertexShader::VertexShader(ID3D11Device* const pDevice, const std::wstring& path)
    {
        Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

        if (FAILED(::D3DReadFileToBlob(path.c_str(), &pBlob)))
        {
            throw std::runtime_error("CANNOT read Vertex Shader to D3D Blob!");
        }

        if (FAILED(pDevice->CreateVertexShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &m_pVertexShader_)))
        {
            throw std::runtime_error("Could NOT create VertexShader!");
        }
    }
    VertexShader::VertexShader(ID3D11Device* const pDevice, const Microsoft::WRL::ComPtr<ID3DBlob>& pBlob)
    {
        if (FAILED(pDevice->CreateVertexShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &m_pVertexShader_)))
        {
            throw std::runtime_error("Could NOT create VertexShader!");
        }
    }


    void VertexShader::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->VSSetShader(m_pVertexShader_.Get(), nullptr, 0U);
    }
}

#endif
