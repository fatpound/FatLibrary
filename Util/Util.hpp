#pragma once

#include <FatMacros.hpp>

#include "Math/Numbers/Sets.hpp"

#include "Gfx/Gfx.hpp"
#include "Timer.hpp"
#include "Color.hpp"
#include "Surface.hpp"
#include "ViewXM.hpp"

#include <concepts>

namespace fatpound::util
{
    template
    <
        ::std::unsigned_integral U,
        ::std::floating_point F = float
    >
    FAT_CMATH_CONSTEXPR23
    static auto HourMinuteHandAngle(U hours, U minutes) -> F
    {
        hours   %= 12;
        minutes %= 60;

        const auto angle = std::fabs((11 * minutes - 60 * hours) / 2);

        return (angle > 180) ? (360 - angle) : angle;
    }
}