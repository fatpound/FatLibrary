#pragma once

#include "Numset/Numset.hpp"

#include "Multiplicable.hpp"
#include "Primes.hpp"

#include <DirectXMath.h>

#include <cmath>

#include <numbers>

namespace fatpound::math
{
    template <Squarable T>
    inline constexpr auto Square(const T& x) noexcept(Squarable_NX<T>)
    {
        return x * x;
    }

    template <std::floating_point N>
    inline constexpr auto Gaussian(const N x, const N rho)
    {
        const auto rhoSq2 = Square<>(rho) * 2.0;

        return (1.0 / ::std::sqrt(rhoSq2 * ::std::numbers::pi_v<N>)) * ::std::exp(-(Square<>(x) / rhoSq2));
    }

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    auto GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept -> float;
    auto GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept -> float;
}