#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#include "VertexCBuffer.hpp"

#include <Util/ViewXM.hpp>

namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class TransformCBuffer final : public Bindable
    {
    public:
        explicit TransformCBuffer(ID3D11Device* const pDevice, const T& parent, FATSPACE_UTIL::ViewXM& viewXM)
            :
            m_vcbuf_(pDevice),
            m_parent_(parent),
            m_viewXM_(viewXM)
        {
            
        }

        explicit TransformCBuffer()                            = delete;
        explicit TransformCBuffer(const TransformCBuffer&)     = delete;
        explicit TransformCBuffer(TransformCBuffer&&) noexcept = delete;

        auto operator = (const TransformCBuffer&)     -> TransformCBuffer& = delete;
        auto operator = (TransformCBuffer&&) noexcept -> TransformCBuffer& = delete;
        virtual ~TransformCBuffer() noexcept override final                = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            m_vcbuf_.Update(
                pImmediateContext,
                ::DirectX::XMMatrixTranspose(
                    m_parent_.GetTransformXM() *
                    m_viewXM_.GetCameraXM() *
                    m_viewXM_.GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(pImmediateContext);
        }


    protected:


    private:
        VertexCBuffer<::DirectX::XMMATRIX> m_vcbuf_;

        const T& m_parent_;

        FATSPACE_UTIL::ViewXM& m_viewXM_;
    };
}

#endif
