#pragma once

namespace fatpound::util::gfx
{
    struct alignas(8) SizePack final
    {
        unsigned int m_width{};
        unsigned int m_height{};
    };
}