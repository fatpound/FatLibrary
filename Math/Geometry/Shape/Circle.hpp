#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <DirectXMath.h>

#include <Math/Multiplicative.hpp>
#include <Math/Numbers/Common.hpp>
#include <Math/Geometry/Common.hpp>
#include <Math/Geometry/AngularConv.hpp>
#include <Traits/Bitwise.hpp>

#include <concepts>

namespace fatpound::math::geometry
{
    class alignas(32) Circle
    {
        static constexpr auto scx_Default_Z_ = 1.0F;
        static constexpr auto scx_Default_W_ = 1.0F;

    public:
        explicit Circle(const DirectX::XMVECTOR& center, const std::convertible_to<float> auto& radius)
            :
            m_center_(center),
            m_radius_(static_cast<float>(radius))
        {

        }

        explicit Circle(
            const std::convertible_to<float> auto& x,
            const std::convertible_to<float> auto& y,
            const std::convertible_to<float> auto& z,
            const std::convertible_to<float> auto& radius)
            :
            Circle(DirectX::XMVectorSet(x, y, z, scx_Default_W_), radius)
        {

        }

        explicit Circle(
            const std::convertible_to<float> auto& x,
            const std::convertible_to<float> auto& y,
            const std::convertible_to<float> auto& radius)
            :
            Circle(x, y, scx_Default_Z_, radius)
        {

        }

        explicit Circle()         = delete;
        Circle(const Circle&)     = default;
        Circle(Circle&&) noexcept = default;

        auto operator = (const Circle&)     -> Circle& = default;
        auto operator = (Circle&&) noexcept -> Circle& = default;
        ~Circle() noexcept                             = default;


    public:
        template <traits::UIntegralOrFloating T> static constexpr auto Area      (const T& radius) noexcept -> T
        {
            return Square<>(radius) * numbers::Pi<T>;
        }
        template <traits::UIntegralOrFloating T> static constexpr auto Diameter  (const T& radius) noexcept -> T
        {
            return radius * static_cast<T>(2.0);
        }
        template <traits::UIntegralOrFloating T> static constexpr auto Perimeter (const T& radius) noexcept -> T
        {
            return Diameter<>(radius) * numbers::Pi<T>;
        }


    public:
        auto GetCenter    () const noexcept -> DirectX::XMVECTOR
        {
            return m_center_;
        }
        auto GetRadius    () const noexcept -> float
        {
            return m_radius_;
        }
        auto GetArea      () const noexcept -> float
        {
            return Area<>(GetRadius());
        }
        auto GetDiameter  () const noexcept -> float
        {
            return Diameter<>(GetRadius());
        }
        auto GetPerimeter () const noexcept -> float
        {
            return Perimeter<>(GetRadius());
        }

        auto Distance_CenterToCenter (const Circle& other) const noexcept -> float
        {
            return Distance4(GetCenter(), other.GetCenter());
        }
        auto Distance_CenterToEdge   (const Circle& other) const noexcept -> float
        {
            return Distance_CenterToCenter(other) - other.GetRadius();
        }
        auto Distance_EdgeToEdge     (const Circle& other) const noexcept -> float
        {
            return Distance_CenterToEdge(other) - GetRadius();
        }
        auto Distance_EdgeToCenter   (const Circle& other) const noexcept -> float
        {
            return Distance_CenterToCenter(other) - GetRadius();
        }

        auto ArcLengthRad (const float& rad) const noexcept -> float
        {
            return GetRadius() * rad;
        }
        auto ArcLengthDeg (const float& deg) const noexcept -> float
        {
            return ArcLengthRad(DegToRad<>(deg));
        }

        auto IsInsideOf   (const Circle& other) const noexcept -> bool
        {
            return Distance_CenterToCenter(other) + GetRadius() <= other.GetRadius();
        }
        auto Contains     (const Circle& other) const noexcept -> bool
        {
            return Distance_CenterToCenter(other) + other.GetRadius() <= GetRadius();
        }

        void TranslateBy  (const DirectX::XMVECTOR& v) noexcept
        {
            m_center_ = (m_center_ + v);
        }


    protected:


    private:
        DirectX::XMVECTOR   m_center_;
        float               m_radius_;
    };
}

#endif
