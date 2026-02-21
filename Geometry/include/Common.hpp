#pragma once

#include <_macros/STL.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

#include <Math/include/Multiplicative.hpp>

#include <cmath>
#include <concepts>

namespace fatpound::geometry
{
#ifdef FATLIB_BUILDING_WITH_MSVC

    auto operator +       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR;
    auto operator -       (const DirectX::XMVECTOR& p1, const DirectX::XMVECTOR& p0) noexcept -> DirectX::XMVECTOR;
    auto operator *       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR;
    auto operator /       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR;
    auto operator *       (const float&          scale, const DirectX::XMVECTOR&  v) noexcept -> DirectX::XMVECTOR;
    auto operator *       (const DirectX::XMVECTOR&  v, const float&          scale) noexcept -> DirectX::XMVECTOR;
    auto operator /       (const DirectX::XMVECTOR&  v, const float&          scale) noexcept -> DirectX::XMVECTOR;

    auto DistanceVector2  (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR;
    auto DistanceVector3  (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR;
    auto DistanceVector4  (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR;

    auto Distance2        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float;
    auto Distance3        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float;
    auto Distance4        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float;
    auto Distance         (const DirectX::XMFLOAT2& p0, const DirectX::XMFLOAT2& p1) noexcept -> float;
    auto Distance         (const DirectX::XMFLOAT3& p0, const DirectX::XMFLOAT3& p1) noexcept -> float;
    auto Distance         (const DirectX::XMFLOAT4& p0, const DirectX::XMFLOAT4& p1) noexcept -> float;

    auto CompareDistance2 (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> bool;
    auto CompareDistance  (const DirectX::XMFLOAT2& p0, const DirectX::XMFLOAT2& p1) noexcept -> bool;

#endif

    template <std::floating_point T = float, std::convertible_to<T> U>
    CX_MATH26 auto Hypotenuse(const U& x, const U& y) noexcept -> T
    {
        return std::sqrt(math::Square<>(x) + math::Square<>(y));
    }
}
