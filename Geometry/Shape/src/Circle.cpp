#include "Circle.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Geometry/include/Common.hpp>

namespace fatpound::geometry::shape
{
    auto Circle::GetCenter    () const noexcept -> DirectX::XMVECTOR
    {
        return m_center_;
    }
    auto Circle::GetRadius    () const noexcept -> float
    {
        return m_radius_;
    }
    auto Circle::GetArea      () const noexcept -> float
    {
        return S_Area<>(GetRadius());
    }
    auto Circle::GetDiameter  () const noexcept -> float
    {
        return S_Diameter<>(GetRadius());
    }
    auto Circle::GetPerimeter () const noexcept -> float
    {
        return S_Perimeter<>(GetRadius());
    }

    auto Circle::ArcLengthRad (const float& rad) const noexcept -> float
    {
        return GetRadius() * rad;
    }
    auto Circle::ArcLengthDeg (const float& deg) const noexcept -> float
    {
        return ArcLengthRad(DegToRad<>(deg));
    }

    auto Circle::IsInsideOf   (const Circle& other) const noexcept -> bool
    {
        return Distance_CenterToCenter(other) + GetRadius() <= other.GetRadius();
    }
    auto Circle::Contains     (const Circle& other) const noexcept -> bool
    {
        return Distance_CenterToCenter(other) + other.GetRadius() <= GetRadius();
    }

    void Circle::TranslateBy  (const DirectX::XMVECTOR& v) noexcept
    {
        m_center_ += v;
    }

    auto Circle::Distance_CenterToCenter (const Circle& other) const noexcept -> float
    {
        return Distance4(GetCenter(), other.GetCenter());
    }
    auto Circle::Distance_CenterToEdge   (const Circle& other) const noexcept -> float
    {
        return Distance_CenterToCenter(other) - other.GetRadius();
    }
    auto Circle::Distance_EdgeToEdge     (const Circle& other) const noexcept -> float
    {
        return Distance_CenterToEdge(other) - GetRadius();
    }
    auto Circle::Distance_EdgeToCenter   (const Circle& other) const noexcept -> float
    {
        return Distance_CenterToCenter(other) - GetRadius();
    }
}

#endif
