module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "Triangle.hpp"
#endif

export module FatPound.Geometry.Shape.Triangle;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::geometry
{
    using shape::Triangle;
}

#endif

// module : private;
