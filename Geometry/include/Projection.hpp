#pragma once

#include <concepts>

namespace fatpound::geometry
{
    template <std::floating_point T = float>
    inline constexpr auto UnprojectPixelCoordinate(const T& pixelCoord, const T& centerCoord, const T& pixelDepth, const T& focalLength) noexcept -> T
    {
        return (pixelCoord - centerCoord) * pixelDepth / focalLength;
    }
}
