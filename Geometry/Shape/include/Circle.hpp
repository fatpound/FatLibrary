#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Geometry/include/Common.hpp>
#include <Geometry/include/AngularConv.hpp>

#include <Math/include/Multiplicative.hpp>
#include <Math/Numbers/include/Common.hpp>
#include <Traits/include/Bitwise.hpp>

#include <DirectXMath.h>

#include <concepts>

namespace fatpound::geometry::shape
{
    class alignas(32) Circle
    {
        static constexpr auto scx_Default_Z_ = 1.0F;
        static constexpr auto scx_Default_W_ = 1.0F;

    public:
        explicit Circle(const DirectX::XMVECTOR& center, const std::convertible_to<float> auto& radius);

        explicit Circle(
            const std::convertible_to<float> auto& x,
            const std::convertible_to<float> auto& y,
            const std::convertible_to<float> auto& z,
            const std::convertible_to<float> auto& radius);

        explicit Circle(
            const std::convertible_to<float> auto& x,
            const std::convertible_to<float> auto& y,
            const std::convertible_to<float> auto& radius);

        explicit Circle()         = delete;
        Circle(const Circle&)     = default;
        Circle(Circle&&) noexcept = default;

        auto operator = (const Circle&)     -> Circle& = default;
        auto operator = (Circle&&) noexcept -> Circle& = default;
        ~Circle() noexcept                             = default;


    public:
        template <traits::UIntegralOrFloating T> static constexpr auto Area      (const T& radius) noexcept -> T
        {
            return math::Square<>(radius) * math::numbers::Pi<T>;
        }
        template <traits::UIntegralOrFloating T> static constexpr auto Diameter  (const T& radius) noexcept -> T
        {
            return radius * static_cast<T>(2.0);
        }
        template <traits::UIntegralOrFloating T> static constexpr auto Perimeter (const T& radius) noexcept -> T
        {
            return Diameter<>(radius) * math::numbers::Pi<T>;
        }


    public:
        auto GetCenter    () const noexcept -> DirectX::XMVECTOR;
        auto GetRadius    () const noexcept -> float;
        auto GetArea      () const noexcept -> float;
        auto GetDiameter  () const noexcept -> float;
        auto GetPerimeter () const noexcept -> float;

        auto Distance_CenterToCenter (const Circle& other) const noexcept -> float;
        auto Distance_CenterToEdge   (const Circle& other) const noexcept -> float;
        auto Distance_EdgeToEdge     (const Circle& other) const noexcept -> float;
        auto Distance_EdgeToCenter   (const Circle& other) const noexcept -> float;

        auto ArcLengthRad (const float& rad) const noexcept -> float;
        auto ArcLengthDeg (const float& deg) const noexcept -> float;

        auto IsInsideOf   (const Circle& other) const noexcept -> bool;
        auto Contains     (const Circle& other) const noexcept -> bool;

        void TranslateBy  (const DirectX::XMVECTOR& v) noexcept;


    protected:


    private:
        DirectX::XMVECTOR   m_center_;
        float               m_radius_;
    };
}

#endif
