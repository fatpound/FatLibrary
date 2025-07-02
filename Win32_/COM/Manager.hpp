#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/WinAPI.hpp>

#include <combaseapi.h>

#include <stdexcept>

namespace fatpound::win32::com
{
    /// @brief Manages the initialization and uninitialization of the COM library for the current thread
    ///
    class Manager final
    {
    public:
        explicit Manager(const DWORD initFlags = COINIT_APARTMENTTHREADED bitor COINIT_DISABLE_OLE1DDE)
        {
            if (FAILED(::CoInitializeEx(nullptr, initFlags)))
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
