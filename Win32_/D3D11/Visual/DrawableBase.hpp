#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatNamespaces.hpp>

#include <Win32_/D3D11/Pipeline/Pipeline.hpp>
#include <Win32_/D3D11/Visual/Drawable.hpp>

#include <cassert>

#include <vector>
#include <typeinfo>
#include <memory>

namespace fatpound::win32::d3d11::visual
{
    template <typename T>
    class DrawableBase : public Drawable
    {
    public:
        explicit DrawableBase()                    = default;
        explicit DrawableBase(const DrawableBase&) = delete;
        explicit DrawableBase(DrawableBase&&)      = delete;

        auto operator = (const DrawableBase&) -> DrawableBase& = delete;
        auto operator = (DrawableBase&&)      -> DrawableBase& = delete;
        virtual ~DrawableBase() noexcept override              = default;


    public:
        static auto IsStaticInitialized_() noexcept -> bool
        {
            return not tl_bindable_vec_.empty();
        }
        static void AddStaticBind_(std::unique_ptr<pipeline::Bindable> bind) noexcept(IN_RELEASE)
        {
            assert((typeid(*bind) not_eq typeid(pipeline::IndexBuffer)) && "*Must* use AddIndexBuffer_() method to bind it!");

            tl_bindable_vec_.push_back(std::move<>(bind));
        }


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<pipeline::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" and m_pCIndexBuffer_ == nullptr);

            m_pCIndexBuffer_ = idxbuf.get();

            tl_bindable_vec_.push_back(std::move<>(idxbuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" and m_pCIndexBuffer_ == nullptr);

            for (const auto& b : GetStaticBinds_())
            {
                const auto* const ptr = dynamic_cast<pipeline::IndexBuffer*>(b.get());

                if (ptr not_eq nullptr)
                {
                    m_pCIndexBuffer_ = ptr;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" and m_pCIndexBuffer_ not_eq nullptr);
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
