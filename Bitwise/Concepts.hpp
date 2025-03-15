#pragma once

#include <concepts>

namespace fatpound::bitwise
{
    template <typename T> concept Unsigned_Integral_Or_Floating = ::std::unsigned_integral<T> or ::std::floating_point<T>;
    template <typename T> concept   Signed_Integral_Or_Floating =   ::std::signed_integral<T> or ::std::floating_point<T>;
    template <typename T> concept          Integral_Or_Floating =          ::std::integral<T> or ::std::floating_point<T>;
}
