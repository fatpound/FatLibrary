#include <Win32_/GDI_Plus/Manager.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <gdiplus.h>

#include <stdexcept>

#pragma comment(lib, "gdiplus")

namespace fatpound::win32::gdi_plus
{
    Manager::Manager()
    {
        if (s_ref_count_ == 0)
        {
            const Gdiplus::GdiplusStartupInput gdiplusStartupInput;

            const auto& status = Gdiplus::GdiplusStartup(&s_gdiPlus_token_, &gdiplusStartupInput, nullptr);

            if (status not_eq Gdiplus::Ok)
            {
                throw std::runtime_error("GDI+ initialization failed");
            }
        }

        ++s_ref_count_;
    }
    Manager::~Manager() noexcept
    {
        --s_ref_count_;

        if (s_ref_count_ == 0)
        {
            Gdiplus::GdiplusShutdown(s_gdiPlus_token_);
        }
    }
}

#endif
