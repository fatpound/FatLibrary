module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "Circle.hpp"
#endif

export module FatPound.Geometry.Shape.Circle;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::geometry
{
    using shape::Circle;
}

#endif

// module : private;
