#pragma once

#include <FatDefines.hpp>

#include "Gfx/Gfx.hpp"

#include "Common.hpp"
#include "Timer.hpp"
#include "Color.hpp"
#include "Surface.hpp"
#include "ViewXM.hpp"

#include <concepts>

namespace fatpound::util
{
    template <::std::floating_point FP = float, ::std::integral I>
    FAT_CMATH_CONSTEXPR23
    static auto HourMinuteHandAngle(I hours, I minutes) -> FP
    {
        if constexpr (::std::signed_integral<I>)
        {
            if (hours < 0)
            {
                hours = -hours;
            }

            if (minutes < 0)
            {
                minutes = -minutes;
            }
        }

        hours   %= 12;
        minutes %= 60;

        const auto& angle = ::std::fabs(static_cast<FP>((11 * minutes) - (60 * hours)) / static_cast<FP>(2));

        return (angle > 180) ? static_cast<FP>(360 - angle) : angle;
    }
}
