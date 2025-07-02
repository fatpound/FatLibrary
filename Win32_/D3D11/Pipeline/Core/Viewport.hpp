#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>
#include <d3d11.h>

#include <Win32_/D3D11/Pipeline/Bindable.hpp>

namespace fatpound::win32::d3d11::pipeline
{
    class Viewport : public Bindable
    {
    public:
        explicit Viewport(const D3D11_VIEWPORT& vp) noexcept
            :
            m_vp_(vp)
        {
            
        }

        explicit Viewport()                    = delete;
        explicit Viewport(const Viewport&)     = delete;
        explicit Viewport(Viewport&&) noexcept = delete;

        auto operator = (const Viewport&)     -> Viewport& = delete;
        auto operator = (Viewport&&) noexcept -> Viewport& = delete;
        virtual ~Viewport() noexcept override              = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->RSSetViewports(1U, &m_vp_);
        }


    protected:
        D3D11_VIEWPORT  m_vp_;


    private:
    };
}

#endif
