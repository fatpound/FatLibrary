#pragma once

#include <concepts>

namespace fatpound::bitwise
{
    template <typename T> concept UIntegralOrFloating = std::unsigned_integral<T> or std::floating_point<T>;
    template <typename T> concept SIntegralOrFloating = std::signed_integral<T>   or std::floating_point<T>;
    template <typename T> concept  IntegralOrFloating = std::integral<T>          or std::floating_point<T>;
}
