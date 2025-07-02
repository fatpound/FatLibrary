#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/STL.hpp>

#include <DirectXMath.h>

#include <Traits/Bitwise.hpp>

#include <cstdlib>
#include <cmath>

namespace fatpound::math::geometry
{
    class alignas(32) Triangle
    {
    public:
        explicit Triangle() noexcept           = default;
        explicit Triangle(const Triangle&)     = default;
        explicit Triangle(Triangle&&) noexcept = default;

        auto operator = (const Triangle&)     -> Triangle& = default;
        auto operator = (Triangle&&) noexcept -> Triangle& = default;
        ~Triangle() noexcept                               = default;


    public:
        template <traits::UIntegralOrFloating T> static constexpr auto IsInequal         (const T& a, const T& b, const T& c) noexcept -> bool
        {
            return     ((std::abs(b - c) < a) and (a < (b + c)))
                   and ((std::abs(a - c) < b) and (b < (a + c)))
                   and ((std::abs(a - b) < c) and (c < (a + b)));
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

    protected:


    private:
        DirectX::XMVECTOR   m_va_;
        DirectX::XMVECTOR   m_vb_;
        DirectX::XMVECTOR   m_vc_;
    };
}

#endif
