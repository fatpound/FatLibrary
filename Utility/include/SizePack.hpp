#pragma once

#include <cstddef>

namespace fatpound::utility
{
    struct alignas(16) SizePack
    {
        std::size_t   m_width{};
        std::size_t   m_height{};
    };
}
