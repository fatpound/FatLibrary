#pragma once

#include <concepts>
#include <numbers>

namespace fatpound::math::numbers
{
    template <std::floating_point FP = double> constexpr auto    Pi = std::numbers::pi_v<FP>;
    template <std::floating_point FP = double> constexpr auto twoPi = Pi<FP> *static_cast<FP>(2.0);
}
