#pragma once

#include "FatGst.hpp"

namespace fatx::gstreamer
{
    class Manager final
    {
    public:
        explicit Manager(int& argc, char**& argv) noexcept
        {
            gst_init(&argc, &argv);
        }
        explicit Manager(const Manager&)     = default;
        explicit Manager(Manager&&) noexcept = default;

        auto operator = (const Manager&)     -> Manager& = default;
        auto operator = (Manager&&) noexcept -> Manager& = default;
        ~Manager() noexcept
        {
            gst_deinit();
        }


    protected:


    private:
    };
}
