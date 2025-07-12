#pragma once

#include <numbers>
#include <concepts>

namespace fatpound::math::numbers
{
    template <std::floating_point T = float> static constexpr auto       Pi = std::numbers::pi_v<T>;
    template <std::floating_point T = float> static constexpr auto    twoPi = Pi<T> * static_cast<T>(2.0);
    template <std::floating_point T = float> static constexpr auto   PiDiv2 = Pi<T> / static_cast<T>(2.0);
    template <std::floating_point T = float> static constexpr auto   PiDiv4 = Pi<T> / static_cast<T>(4.0);
    template <std::floating_point T = float> static constexpr auto    invPi = static_cast<T>(1.0) / Pi<T>;
    template <std::floating_point T = float> static constexpr auto invTwoPi = invPi<T> / static_cast<T>(2.0);
}