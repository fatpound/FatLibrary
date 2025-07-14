#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

#include <string>

namespace fatpound::win32::d3d11::pipeline
{
    class VertexShader : public Bindable
    {
    public:
        explicit VertexShader(ID3D11Device* const pDevice, const std::wstring& path);
        explicit VertexShader(ID3D11Device* const pDevice, const Microsoft::WRL::ComPtr<ID3DBlob>& pBlob);

        explicit VertexShader()                        = delete;
        explicit VertexShader(const VertexShader&)     = delete;
        explicit VertexShader(VertexShader&&) noexcept = delete;

        auto operator = (const VertexShader&)     -> VertexShader& = delete;
        auto operator = (VertexShader&&) noexcept -> VertexShader& = delete;
        virtual ~VertexShader() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11VertexShader>  m_pVertexShader_;


    private:
    };
}

#endif
