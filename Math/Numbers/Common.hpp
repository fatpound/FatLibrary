#pragma once

#include <numbers>
#include <concepts>

namespace fatpound::math::numbers
{
    template <std::floating_point FP = double> static constexpr auto       Pi = std::numbers::pi_v<FP>;
    template <std::floating_point FP = double> static constexpr auto    twoPi = Pi<FP> * static_cast<FP>(2.0);
    template <std::floating_point FP = double> static constexpr auto   PiDiv2 = Pi<FP> / static_cast<FP>(2.0);
    template <std::floating_point FP = double> static constexpr auto   PiDiv4 = Pi<FP> / static_cast<FP>(4.0);
    template <std::floating_point FP = double> static constexpr auto    invPi = static_cast<FP>(1.0) / Pi<FP>;
    template <std::floating_point FP = double> static constexpr auto invTwoPi = invPi<FP> / static_cast<FP>(2.0);
}
