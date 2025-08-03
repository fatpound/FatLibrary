#include "ResourcePack.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::d3d11
{
    FrameworkResourcePack::FrameworkResourcePack(const utility::SizePack& dimensions)
        :
        m_surface(dimensions)
    {

    }
}

#endif
