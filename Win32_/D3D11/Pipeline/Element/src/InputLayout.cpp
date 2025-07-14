#include <Win32_/D3D11/Pipeline/Element/include/InputLayout.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    InputLayout::InputLayout(ID3D11Device* const pDevice, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const Microsoft::WRL::ComPtr<ID3DBlob>& pVertexShaderBytecode)
    {
        if (FAILED(pDevice->CreateInputLayout(
            layout.data(),
            static_cast<UINT>(layout.size()),
            pVertexShaderBytecode->GetBufferPointer(),
            pVertexShaderBytecode->GetBufferSize(),
            &m_pInputLayout_)))
        {
            throw std::runtime_error("Could NOT create InputLayout!");
        }
    }


    void InputLayout::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->IASetInputLayout(m_pInputLayout_.Get());
    }
}

#endif
