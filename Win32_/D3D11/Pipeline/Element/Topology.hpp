#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatWin32.hpp>

#include <d3d11.h>

#include "../Bindable.hpp"

namespace fatpound::win32::d3d11::pipeline::element
{
    class Topology final : public Bindable
    {
    public:
        explicit Topology(const D3D11_PRIMITIVE_TOPOLOGY type) noexcept
            :
            m_type_(type)
        {

        }

        explicit Topology()                    = delete;
        explicit Topology(const Topology&)     = delete;
        explicit Topology(Topology&&) noexcept = delete;

        auto operator = (const Topology&)     -> Topology& = delete;
        auto operator = (Topology&&) noexcept -> Topology& = delete;
        virtual ~Topology() noexcept override final        = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->IASetPrimitiveTopology(m_type_);
        }


    protected:
        D3D11_PRIMITIVE_TOPOLOGY m_type_;


    private:
    };
}

#endif
