#pragma once

#include <Traits/include/Bitwise.hpp>

#include <concepts>

namespace fatpound::math::numbers
{
    template <typename T> concept Natural  = std::unsigned_integral<T>;
    template <typename T> concept Integer  = std::integral<T>;
    template <typename T> concept Rational = traits::IntegralOrFloating<T>;
}
