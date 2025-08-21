#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <d3d11_4.h>

#include <Win32_/D3D11/include/Bindable.hpp>

namespace fatpound::win32::d3d11::core
{
    class Topology : public Bindable
    {
    public:
        explicit Topology(const D3D11_PRIMITIVE_TOPOLOGY& type) noexcept;

        explicit Topology()                    = delete;
        explicit Topology(const Topology&)     = delete;
        explicit Topology(Topology&&) noexcept = default;

        auto operator = (const Topology&)     -> Topology& = delete;
        auto operator = (Topology&&) noexcept -> Topology& = default;
        virtual ~Topology() noexcept override              = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY  m_type_;


    private:
    };
}

#endif
