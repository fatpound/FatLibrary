#pragma once

#if FAT_BUILDING_WITH_MSVC

#define FATPOUND_FULL_WIN_TARGETED
#include <FatWin32.hpp>
#include <gdiplus.h>
#undef FATPOUND_FULL_WIN_TARGETED

#pragma comment(lib, "gdiplus")

#include <stdexcept>

namespace fatpound::win32::gdi_plus
{
    class Manager final
    {
    public:
        explicit Manager()
        {
            if (s_ref_count_ == 0)
            {
                const ::Gdiplus::GdiplusStartupInput gdiplusStartupInput;

                const auto success = ::Gdiplus::GdiplusStartup(&s_gdiPlus_token_, &gdiplusStartupInput, nullptr);

                if (success not_eq ::Gdiplus::Ok)
                {
                    throw std::runtime_error("GDI+ initialization failed");
                }
            }

            ++s_ref_count_;
        }
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            --s_ref_count_;

            if (s_ref_count_ == 0)
            {
                ::Gdiplus::GdiplusShutdown(s_gdiPlus_token_);
            }
        }


    protected:


    private:
        inline static ::ULONG_PTR s_gdiPlus_token_{};

        inline static int s_ref_count_{};
    };
}

#endif
