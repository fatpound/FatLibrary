#pragma once

#include <FatMacros.hpp>

#include "../Common.hpp"

#include "Primes.hpp"
#include "Sets.hpp"

#include <numbers>

namespace fatpound::math::numbers
{
    template <Rational Q>
    constexpr auto twoPi = std::numbers::pi_v<Q> * static_cast<Q>(2.0);

    template <Integer Z>
    static constexpr auto IsOdd(const Z& num) noexcept -> bool
    {
        return num bitand static_cast<Z>(1);
    }

    template <Integer Z>
    static constexpr auto IsEven(const Z& num) noexcept -> bool
    {
        return not IsOdd<>(num);
    }

    template <Natural N>
    static constexpr auto IsPowerOf2(const N& num) noexcept -> bool
    {
        return (num not_eq 0) and (not (num bitand (num - 1)));
    }

    template <Natural N>
    FAT_CMATH_CONSTEXPR23
    static auto IsSquare(const N& num) noexcept -> bool
    {
        return Square<N>(std::sqrt(num)) == num;
    }

    template <Natural N>
    FAT_CMATH_CONSTEXPR23
    static auto IsCube(const N& num) noexcept -> bool
    {
        return Cube<N>(std::cbrt(num)) == num;
    }

    template <Natural N>
    static constexpr auto IsPerfectSquare(const N& num) noexcept -> bool
    {
        return IsSquare<>(num);
    }

    template <Natural N>
    static constexpr auto IsPerfectCube(const N& num) noexcept -> bool
    {
        return IsCube<>(num);
    }

    template <Natural N>
    static constexpr auto IsHarshad(const N& num) noexcept -> bool
    {
        return num % DigitSum<>(num) == 0;
    }

    template <Natural N>
    static constexpr auto IsNiven(const N& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }

    template <Natural N>
    static constexpr auto IsMultidigital(const N& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }
}
