#pragma once

#include <FatDefines.hpp>

#include "../Common.hpp"

#include "Primes.hpp"
#include "Sets.hpp"

#include <numbers>

namespace fatpound::math::numbers
{
    template <::std::floating_point FP> constexpr auto    Pi = std::numbers::pi_v<FP>;
    template <::std::floating_point FP> constexpr auto twoPi = std::numbers::pi_v<FP> * static_cast<FP>(2.0);

    template <::std::unsigned_integral T> FAT_CMATH_CONSTEXPR23 auto IsSquare        (const T& num) noexcept -> bool
    {
        return Square<T>(std::sqrt(num)) == num;
    }
    template <::std::unsigned_integral T> FAT_CMATH_CONSTEXPR23 auto IsCube          (const T& num) noexcept -> bool
    {
        return Cube<T>(std::cbrt(num)) == num;
    }
    template <::std::unsigned_integral T>             constexpr auto IsPerfectSquare (const T& num) noexcept -> bool
    {
        return IsSquare<>(num);
    }
    template <::std::unsigned_integral T>             constexpr auto IsPerfectCube   (const T& num) noexcept -> bool
    {
        return IsCube<>(num);
    }
    template <::std::unsigned_integral T>             constexpr auto IsHarshad       (const T& num) noexcept -> bool
    {
        return num % DigitSum<>(num) == 0;
    }
    template <::std::unsigned_integral T>             constexpr auto IsNiven         (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }
    template <::std::unsigned_integral T>             constexpr auto IsMultidigital  (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }

    template <::std::integral T>                      constexpr auto IsOdd           (const T& num) noexcept -> bool
    {
        return num bitand static_cast<T>(1);
    }
    template <::std::integral T>                      constexpr auto IsEven          (const T& num) noexcept -> bool
    {
        return not IsOdd<>(num);
    }
}
