module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "ResourcePack.hpp"
#endif

export module FatPound.Utility.Gfx.ResourcePack;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::utility
{
    using gfx::ResourcePack;
    using gfx::FrameworkResourcePack;
}

#endif

// module : private;
