#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/WinAPI.hpp>
#include <d3d11_4.h>
#include <wrl.h>

namespace fatpound::win32::d3d11
{
    class Bindable
    {
    public:
        explicit Bindable()                    = default;
        explicit Bindable(const Bindable&)     = default;
        explicit Bindable(Bindable&&) noexcept = default;

        auto operator = (const Bindable&)     -> Bindable& = default;
        auto operator = (Bindable&&) noexcept -> Bindable& = default;
        virtual ~Bindable() noexcept                       = default;
        

    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) = 0;


    protected:


    private:
    };
}

#endif
