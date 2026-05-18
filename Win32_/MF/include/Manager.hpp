#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::mf
{
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
    };
}

#endif
