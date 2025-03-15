#pragma once

#if defined(_MSC_VER)

#include <FatNamespaces.hpp>

#include "../Pipeline/Pipeline.hpp"

#include "Drawable.hpp"

#include <cassert>

#include <memory>

namespace fatpound::win32::d3d11::visual
{
    template <typename T>
    class DrawableBase : public Drawable
    {
    public:
        explicit DrawableBase() = default;
        explicit DrawableBase(const DrawableBase& src) = delete;
        explicit DrawableBase(DrawableBase&& src) = delete;

        auto operator = (const DrawableBase& src) -> DrawableBase& = delete;
        auto operator = (DrawableBase&& src)      -> DrawableBase& = delete;
        virtual ~DrawableBase() noexcept = default;


    public:
        static auto IsStaticInitialized_() -> bool
        {
            return not tl_bindable_vec_.empty();
        }
        static void AddStaticBind_(std::unique_ptr<FATSPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE)
        {
            assert((typeid(*bind) not_eq typeid(FATSPACE_PIPELINE_ELEMENT::IndexBuffer)) && "*Must* use AddIndexBuffer_() method to bind it!");

            tl_bindable_vec_.push_back(std::move(bind));
        }


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<FATSPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && m_pCIndexBuffer_ == nullptr);

            m_pCIndexBuffer_ = idxbuf.get();

            tl_bindable_vec_.push_back(std::move(idxbuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && m_pCIndexBuffer_ == nullptr);

            for (const auto& b : GetStaticBinds_())
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
            return tl_bindable_vec_;
        }


    private:
        inline static thread_local std::vector<BindablePtr_t> tl_bindable_vec_;
    };
}

#endif
