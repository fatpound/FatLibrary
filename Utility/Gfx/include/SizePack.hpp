#pragma once

#include <cstddef>

namespace fatpound::utility::gfx
{
    struct alignas(16) SizePack final
    {
        std::size_t   m_width{};
        std::size_t   m_height{};
    };
}
