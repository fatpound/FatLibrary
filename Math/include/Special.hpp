#pragma once

#include <_macros/STL.hpp>

#include <Math/include/Multiplicative.hpp>
#include <Numbers/include/Common.hpp>
#include <Traits/include/Bitwise.hpp>

#include <cmath>

namespace fatpound::math
{
    template <traits::IntegralOrFloating T>
    CX_MATH26 inline auto Gaussian(const T& x, const T& rho)
    {
        const auto rhoSq2 = Square<>(rho) * 2.0;

        return (1.0 / std::sqrt(rhoSq2 * numbers::Pi<T>)) * std::exp(-(Square<>(x) / rhoSq2));
    }
}
