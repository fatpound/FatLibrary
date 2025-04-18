#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <FatWin32.hpp>

#include <mfapi.h>

#include <stdexcept>

namespace fatpound::win32::wmf
{
    class Manager final
    {
    public:
        explicit Manager()
        {
            const auto hr = ::MFStartup(MF_VERSION);

            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to initialize Media Foundation.");
            }
        }
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            ::MFShutdown();
        }


    protected:


    private:
    };
}

#endif
