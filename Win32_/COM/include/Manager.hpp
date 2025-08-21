#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>

#include <combaseapi.h>

namespace fatpound::win32::com
{
    /// @brief Manages the initialization and uninitialization of the COM library for the current thread
    ///
    class Manager final
    {
    public:
        explicit Manager(const DWORD& initFlags = COINIT_APARTMENTTHREADED bitor COINIT_DISABLE_OLE1DDE);
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept;


    protected:


    private:
    };
}

#endif
