#pragma once

#include <cstdint>

namespace fatpound::util::gfx
{
    struct alignas(8) SizePack final
    {
        ::std::uint32_t m_width{};
        ::std::uint32_t m_height{};
    };
}
