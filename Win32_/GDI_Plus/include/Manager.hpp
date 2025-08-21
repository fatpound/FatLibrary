#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#define FATPOUND_FULL_WIN_TARGETED
#include <Win32_/include/FatWin.hpp>
#undef FATPOUND_FULL_WIN_TARGETED

namespace fatpound::win32::gdi_plus
{
    /// @brief Manages the initialization and shutdown of the GDI+ library using reference counting.
    ///        Ensures GDI+ is started once and properly shut down when no longer needed
    ///
    class Manager final
    {
    public:
        explicit Manager();
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept;


    protected:


    private:
        inline static ULONG_PTR      s_gdiPlus_token_{};
        inline static unsigned int   s_ref_count_{};
    };
}

#endif
