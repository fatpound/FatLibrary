#pragma once

#include <FatWin32.hpp>

#include <mfapi.h>

#include <stdexcept>

namespace fatpound::win32::wmf
{
    class Manager final
    {
    public:
        Manager()
        {
            const auto hr = ::MFStartup(MF_VERSION);

            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to initialize Media Foundation.");
            }
        }
        Manager(const Manager& src) = delete;
        Manager(Manager&& src) = delete;

        auto operator = (const Manager& src) -> Manager& = delete;
        auto operator = (Manager&& src)      -> Manager& = delete;
        ~Manager() noexcept
        {
            ::MFShutdown();
        }


    protected:


    private:
    };
}