#pragma once

#include <Bitwise/Concepts.hpp>

#include <concepts>

namespace fatpound::math::numbers
{
    template <typename T> concept Natural  = ::std::unsigned_integral<T>;
    template <typename T> concept Integer  = ::std::integral<T>;
    template <typename T> concept Rational = bitwise::Integral_Or_Floating<T>;
}
