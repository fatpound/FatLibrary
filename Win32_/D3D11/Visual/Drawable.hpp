#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include "../Pipeline/Element/IndexBuffer.hpp"

#include <cassert>

#include <vector>
#include <memory>

namespace fatpound::win32::d3d11::visual
{
    class Drawable
    {
    public:
        using BindablePtr_t = std::unique_ptr<FATSPACE_PIPELINE::Bindable>;
        using BindableVec_t = std::vector<BindablePtr_t>;


    public:
        explicit Drawable()                    = default;
        explicit Drawable(const Drawable&)     = delete;
        explicit Drawable(Drawable&&) noexcept = delete;

        auto operator = (const Drawable&)     -> Drawable& = delete;
        auto operator = (Drawable&&) noexcept -> Drawable& = delete;
        virtual ~Drawable() noexcept                       = default;


    public:
        virtual auto GetTransformXM() const noexcept -> ::DirectX::XMMATRIX = 0;

        virtual void Update(const float delta_time) noexcept = 0;

        virtual void Draw(ID3D11DeviceContext* const pImmediateContext) const final
        {
            for (auto& bindable : m_binds_)
            {
                bindable->Bind(pImmediateContext);
            }

            for (auto& static_bindable : this->GetStaticBinds_())
            {
                static_bindable->Bind(pImmediateContext);
            }

            pImmediateContext->DrawIndexed(m_pCIndexBuffer_->GetCount(), 0U, 0);
        }

        
    protected:
        virtual void AddBind_(std::unique_ptr<FATSPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE)final
        {
            assert((typeid(*bind) not_eq typeid(FATSPACE_PIPELINE_ELEMENT::IndexBuffer)) && "*Must* use AddIndexBuffer_() method to bind it!");

            m_binds_.push_back(std::move<>(bind));
        }
        virtual void AddIndexBuffer_(std::unique_ptr<FATSPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert((m_pCIndexBuffer_ == nullptr) && "Attempting to add index buffer a second time");

            m_pCIndexBuffer_ = idxbuf.get();

            m_binds_.push_back(std::move<>(idxbuf));
        }


    protected:
        const FATSPACE_PIPELINE_ELEMENT::IndexBuffer* m_pCIndexBuffer_{};


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const BindableVec_t& = 0;


    private:
        BindableVec_t m_binds_;
    };
}

#endif
