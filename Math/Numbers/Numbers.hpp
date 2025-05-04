#pragma once

#include <FatDefines.hpp>

#include <Math/Numbers/Common.hpp>
#include <Math/Numbers/Primes.hpp>
#include <Math/Numbers/Sets.hpp>

#include <Math/Common.hpp>
#include <Math/Multiplicative.hpp>

#include <numbers>

namespace fatpound::math::numbers
{
    template <std::unsigned_integral T> FAT_CMATH_CONSTEXPR26 auto IsSquare        (const T& num) noexcept -> bool
    {
        return Square<T>(std::sqrt(num)) == num;
    }
    template <std::unsigned_integral T> FAT_CMATH_CONSTEXPR26 auto IsCube          (const T& num) noexcept -> bool
    {
        return Cube<T>(std::cbrt(num)) == num;
    }
    template <std::unsigned_integral T>             constexpr auto IsPerfectSquare (const T& num) noexcept -> bool
    {
        return IsSquare<>(num);
    }
    template <std::unsigned_integral T>             constexpr auto IsPerfectCube   (const T& num) noexcept -> bool
    {
        return IsCube<>(num);
    }
    template <std::unsigned_integral T>             constexpr auto IsHarshad       (const T& num) noexcept -> bool
    {
        return num % DigitSum<>(num) == 0;
    }
    template <std::unsigned_integral T>             constexpr auto IsNiven         (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }
    template <std::unsigned_integral T>             constexpr auto IsMultidigital  (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }

    template <std::integral T>                      constexpr auto IsOdd           (const T& num) noexcept -> bool
    {
        return num bitand static_cast<T>(1);
    }
    template <std::integral T>                      constexpr auto IsEven          (const T& num) noexcept -> bool
    {
        return not IsOdd<>(num);
    }
}
