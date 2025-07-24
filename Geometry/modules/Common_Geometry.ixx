module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include "../include/Common.hpp"
#endif

export module FatPound.Geometry.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound
{
    using geometry::operator +;
    using geometry::operator -;
    using geometry::operator *;
    using geometry::operator /;

    using geometry::CompareDistance;
    using geometry::CompareDistance2;
    using geometry::DistanceVector2;
    using geometry::DistanceVector3;
    using geometry::DistanceVector4;
    using geometry::Distance;
    using geometry::Distance2;
    using geometry::Distance3;
    using geometry::Distance4;
}

#endif

// module : private;
