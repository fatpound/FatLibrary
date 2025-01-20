#pragma once

#include <FatNamespaces.hpp>

#include "../Pipeline/Pipeline.hpp"

#include "Drawable.hpp"

#include <cassert>

#include <memory>

namespace fatpound::win32::d3d11::visual
{
    template <typename T>
    class DrawableBase : public Drawable, public pipeline::StaticBindableVec<DrawableBase<T>> // removed FATSPACE_PIPELINE macro from here for Class Designer to find that base class
    {
    public:
        explicit DrawableBase() = default;
        explicit DrawableBase(const DrawableBase& src) = delete;
        explicit DrawableBase(DrawableBase&& src) = delete;

        auto operator = (const DrawableBase& src) -> DrawableBase& = delete;
        auto operator = (DrawableBase&& src)      -> DrawableBase& = delete;
        virtual ~DrawableBase() noexcept = default;


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<FATSPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && m_pCIndexBuffer_ == nullptr);

            m_pCIndexBuffer_ = idxbuf.get();

            this->s_static_binds_.push_back(std::move(idxbuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && m_pCIndexBuffer_ == nullptr);

            for (const auto& b : this->s_static_binds_)
            {
                const auto* const ptr = dynamic_cast<FATSPACE_PIPELINE_ELEMENT::IndexBuffer*>(b.get());

                if (ptr not_eq nullptr)
                {
                    m_pCIndexBuffer_ = ptr;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" && m_pCIndexBuffer_ not_eq nullptr);
        }


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const BindableVec_t& override
        {
            return this->s_static_binds_;
        }
    };
}