#pragma once

#include <FatWin32.hpp>

#include <combaseapi.h>

#include <stdexcept>

namespace fatpound::win32::com
{
    class Manager final
    {
    public:
        Manager(const DWORD initFlags = COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)
        {
            const auto hr = ::CoInitializeEx(nullptr, initFlags);

            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to initialize Media Foundation.");
            }
        }

        Manager() = delete;
        Manager(const Manager& src) = delete;
        Manager(Manager&& src) = delete;

        auto operator = (const Manager& src) -> Manager& = delete;
        auto operator = (Manager&& src)      -> Manager& = delete;
        ~Manager() noexcept
        {
            ::CoUninitialize();
        }


    protected:


    private:
    };
}