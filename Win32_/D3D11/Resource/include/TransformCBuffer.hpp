#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>
#include <wrl.h>

#include <DirectXMath.h>

#include <Win32_/D3D11/include/Bindable.hpp>
#include <Win32_/D3D11/Resource/include/VertexCBuffer.hpp>

#include <Utility/include/ViewXM.hpp>

namespace fatpound::win32::d3d11::resource
{
    template <typename T>
    class TransformCBuffer : public Bindable
    {
    public:
        explicit TransformCBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const T& parent, utility::ViewXM& viewXM)
            :
            m_vcbuf_(pDevice, bufDesc),
            m_parent_(parent),
            m_viewXM_(viewXM)
        {
            
        }

        explicit TransformCBuffer()                            = delete;
        explicit TransformCBuffer(const TransformCBuffer&)     = delete;
        explicit TransformCBuffer(TransformCBuffer&&) noexcept = default;

        auto operator = (const TransformCBuffer&)     -> TransformCBuffer& = delete;
        auto operator = (TransformCBuffer&&) noexcept -> TransformCBuffer& = default;
        virtual ~TransformCBuffer() noexcept override                      = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            m_vcbuf_.Update(
                pImmediateContext,
                DirectX::XMMatrixTranspose(
                    m_parent_.GetTransformXM() *
                    m_viewXM_.GetCameraXM() *
                    m_viewXM_.GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(pImmediateContext);
        }


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX>   m_vcbuf_;

        const T&                           m_parent_;

        utility::ViewXM&                   m_viewXM_;
    };
}

#endif
