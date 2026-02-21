module;

#include "FieldOfView.hpp"

export module FatPound.Geometry.FieldOfView;

export namespace fatpound
{
    using geometry::HFOV;
    using geometry::VFOV;
    using geometry::DFOV;
    using geometry::DFOV_;

    using geometry::HFOV_To_VFOV;
    using geometry::HFOV_To_DFOV;
    using geometry::VFOV_To_HFOV;
    using geometry::VFOV_To_DFOV;
    using geometry::DFOV_To_HFOV;
    using geometry::DFOV_To_VFOV;

    using geometry::FocalLength;
}

// module : private;
