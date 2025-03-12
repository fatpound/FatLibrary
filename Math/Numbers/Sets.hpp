#pragma once

#include <Bitwise/Concepts.hpp>

#include <concepts>

namespace fatpound::math::numbers
{
    template <typename T> concept Natural  = bitwise::Unsigned_Integral<T>;
    template <typename T> concept Integer  = bitwise::Integral<T>;
    template <typename T> concept Rational = bitwise::Integral_Or_Floating<T>;
}