#include "ResourcePack.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::utility::gfx
{
    FrameworkResourcePack::FrameworkResourcePack(const SizePack& dimensions)
        :
        m_surface(dimensions)
    {

    }
}

#endif
