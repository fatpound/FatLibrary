#pragma once

#ifdef _MSC_VER

#include <FatWin32.hpp>

#include <combaseapi.h>

#include <stdexcept>

namespace fatpound::win32::com
{
    /// @brief Manages the initialization and uninitialization of the COM library for the current thread
    ///
    class Manager final
    {
    public:
        explicit Manager(const DWORD initFlags = COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)
        {
            if (const auto& hr = ::CoInitializeEx(nullptr, initFlags);
                FAILED(hr))
            {
                throw std::runtime_error("Failed to initialize COM!");
            }
        }
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            ::CoUninitialize();
        }


    protected:


    private:
    };
}

#endif
