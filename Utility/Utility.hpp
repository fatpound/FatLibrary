#pragma once

#include <FatSTL_Macros.hpp>

#include "Gfx/Gfx.hpp"

#include "Common.hpp"
#include "Timer.hpp"
#include "Color.hpp"
#include "Surface.hpp"
#include "ViewXM.hpp"

#include <concepts>

namespace fatpound::utility
{
    template <std::floating_point FP = double, std::integral T>
    static
    CX_MATH23
    auto ClockHandsAngle(T hours, T minutes) noexcept -> FP
    {
        if constexpr (std::signed_integral<T>)
        {
            hours   = std::abs(hours);
            minutes = std::abs(minutes);
        }

        hours   %= 12;
        minutes %= 60;

        const auto angle = std::fabs(static_cast<FP>((11 * minutes) - (60 * hours)) / static_cast<FP>(2.0));

        return (angle > 180) ? static_cast<FP>(360 - angle) : angle;
    }
    
    constexpr auto StrRev(const std::string& str) -> std::string
    {
        auto revstr = str;

        std::reverse(revstr.begin(), revstr.end());

        return revstr;
    }
}
