#include <Win32_/D3D11/Pipeline/Core/Rasterizer.hpp>

#include <stdexcept>

namespace fatpound::win32::d3d11::pipeline
{
    Rasterizer::Rasterizer(ID3D11Device* const pDevice, const D3D11_RASTERIZER_DESC& rDesc)
    {
        if (FAILED(pDevice->CreateRasterizerState(&rDesc, &m_pRasterizerState_)))
        {
            throw std::runtime_error("Could NOT create RasterizerState!");
        }
    }


    void Rasterizer::Bind(ID3D11DeviceContext* const pImmediateContext)
    {
        pImmediateContext->RSSetState(m_pRasterizerState_.Get());
    }
}
