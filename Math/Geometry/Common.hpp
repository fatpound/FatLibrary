#pragma once

#include <_macros/STL.hpp>

#ifdef FAT_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

#include <Math/Numbers/Common.hpp>
#include <Math/Multiplicative.hpp>
#include <Traits/Bitwise.hpp>

#include <cstdlib>
#include <cmath>

namespace fatpound::math::geometry
{
#ifdef FAT_BUILDING_WITH_MSVC

    static auto operator +      (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorAdd(p0, p1);
    }
    static auto operator -      (const DirectX::XMVECTOR& p1, const DirectX::XMVECTOR& p0) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorSubtract(p1, p0);
    }

    static auto DistanceVector2 (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept
    {
        return DirectX::XMVector2Length(p1 - p0);
    }
    static auto DistanceVector3 (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept
    {
        return DirectX::XMVector3Length(p1 - p0);
    }
    static auto Distance2       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return DirectX::XMVectorGetX(DistanceVector2(p0, p1));
    }
    static auto Distance3       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return DirectX::XMVectorGetX(DistanceVector3(p0, p1));
    }


    /// @brief Calculates distance, 3D by default
    /// 
    /// @param p0: 1st 3D position vector
    /// @param p1: 2nd 3D position vector
    /// 
    /// @return the distance in float type
    static auto Distance        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return Distance3(p0, p1);
    }


    static auto Distance        (const DirectX::XMFLOAT2& p0, const DirectX::XMFLOAT2& p1) noexcept -> float
    {
        return Distance2(DirectX::XMLoadFloat2(&p0), DirectX::XMLoadFloat2(&p1));
    }
    static auto Distance        (const DirectX::XMFLOAT3& p0, const DirectX::XMFLOAT3& p1) noexcept -> float
    {
        return Distance3(DirectX::XMLoadFloat3(&p0), DirectX::XMLoadFloat3(&p1));
    }
    static auto CompareDistance (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept
    {
        return DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(p0)) > DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(p1));
    }

#endif

    template <traits::UIntegralOrFloating T> static constexpr auto SquarePerimeter   (const T& length) noexcept -> T
    {
        return length * static_cast<T>(4);
    }
    template <traits::UIntegralOrFloating T> static constexpr auto SquareArea        (const T& length) noexcept(Squarable_NX<T>) -> T
    {
        return Square<>(length);
    }
    template <traits::UIntegralOrFloating T> static constexpr auto TrianglePerimeter (const T& a, const T& b, const T& c) noexcept -> T
    {
        return a + b + c;
    }
    template <traits::UIntegralOrFloating T> static CX_MATH26 auto TriangleArea      (const T& a, const T& b, const T& c) noexcept -> T
    {
        const auto s = TrianglePerimeter<>(a, b, c) / static_cast<T>(2);

        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    template <traits::UIntegralOrFloating T> static constexpr auto TriangleArea      (const T& height, const T& base) noexcept -> T
    {
        return (base * height) / 2.0;
    }


    /// @brief Checks whether three side lengths can form a triangle
    /// 
    /// @tparam T: A type that is either an unsigned integral or floating-point type, as defined by traits::UIntegralOrFloating
    /// 
    ///  @param a: The length of the  first side
    ///  @param b: The length of the second side
    ///  @param c: The length of the  third side
    /// 
    /// @return true if the three side lengths satisfy the triangle inequality and can form a triangle; otherwise, false
    /// 
    template <traits::UIntegralOrFloating T> static constexpr auto FormsATriangle    (const T& a, const T& b, const T& c) noexcept -> bool
    {
        return     (std::abs(b - c) < a and a < b + c)
               and (std::abs(a - c) < b and b < a + c)
               and (std::abs(a - b) < c and c < a + b);
    }
}