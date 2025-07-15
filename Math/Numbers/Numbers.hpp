#pragma once

#include <_macros/STL.hpp>

#include <Math/include/Common.hpp>
#include <Math/include/Multiplicative.hpp>

#include <Math/Numbers/include/Common.hpp>
#include <Math/Numbers/include/Primes.hpp>
#include <Math/Numbers/include/Sets.hpp>

#include <cmath>

#include <concepts>

namespace fatpound::math::numbers
{
    template <std::unsigned_integral T> static CX_MATH26 auto IsSquare        (const T& num) noexcept -> bool
    {
        return Square<T>(std::sqrt(num)) == num;
    }
    template <std::unsigned_integral T> static CX_MATH26 auto IsCube          (const T& num) noexcept -> bool
    {
        return Cube<T>(std::cbrt(num)) == num;
    }
    template <std::unsigned_integral T> static CX_MATH26 auto IsPerfectSquare (const T& num) noexcept -> bool
    {
        return IsSquare<>(num);
    }
    template <std::unsigned_integral T> static CX_MATH26 auto IsPerfectCube   (const T& num) noexcept -> bool
    {
        return IsCube<>(num);
    }
    template <std::unsigned_integral T> static constexpr auto IsHarshad       (const T& num) noexcept -> bool
    {
        return num % DigitSum<>(num) == 0;
    }
    template <std::unsigned_integral T> static constexpr auto IsNiven         (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }
    template <std::unsigned_integral T> static constexpr auto IsMultidigital  (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }

    template <std::integral T>          static constexpr auto IsOdd           (const T& num) noexcept -> bool
    {
        return num bitand static_cast<T>(1);
    }
    template <std::integral T>          static constexpr auto IsEven          (const T& num) noexcept -> bool
    {
        return not IsOdd<>(num);
    }
}
