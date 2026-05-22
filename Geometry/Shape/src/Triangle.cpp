#include "Triangle.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Geometry/include/Common.hpp>

#include <array>
#include <stdexcept>
#include <algorithm>

namespace fatpound::geometry::shape
{
    Triangle::Triangle(const DirectX::XMVECTOR& va, const DirectX::XMVECTOR& vb, const DirectX::XMVECTOR& vc)
        :
        m_va_(va),
        m_vb_(vb),
        m_vc_(vc)
    {
        if (not S_IsValid<>(GetSideLengthA(), GetSideLengthB(), GetSideLengthC()))
        {
            throw std::invalid_argument("The provided vertices do not form a valid triangle.");
        }
    }


    auto Triangle::GetVertexA            () const noexcept -> DirectX::XMVECTOR
    {
        return m_va_;
    }
    auto Triangle::GetVertexB            () const noexcept -> DirectX::XMVECTOR
    {
        return m_vb_;
    }
    auto Triangle::GetVertexC            () const noexcept -> DirectX::XMVECTOR
    {
        return m_vc_;
    }
    auto Triangle::GetCentroid           () const noexcept -> DirectX::XMVECTOR
    {
        return (m_va_ + m_vb_ + m_vc_) / 3.0F;
    }

    auto Triangle::GetSideLengthA        () const noexcept -> float
    {
        return Distance4(m_vb_, m_vc_);
    }
    auto Triangle::GetSideLengthB        () const noexcept -> float
    {
        return Distance4(m_va_, m_vc_);
    }
    auto Triangle::GetSideLengthC        () const noexcept -> float
    {
        return Distance4(m_va_, m_vb_);
    }

    auto Triangle::GetArea               () const noexcept -> float
    {
        return S_Area<>(GetSideLengthA(), GetSideLengthB(), GetSideLengthC());
    }
    auto Triangle::GetPerimeter          () const noexcept -> float
    {
        return S_Perimeter<>(GetSideLengthA(), GetSideLengthB(), GetSideLengthC());
    }
    auto Triangle::GetIncircleRadius     () const noexcept -> float
    {
        return GetArea() / (GetPerimeter() * 0.5F);
    }
    auto Triangle::GetCircumcircleRadius () const noexcept -> float
    {
        return (GetSideLengthA() * GetSideLengthB() * GetSideLengthC()) / (4.0F * GetArea());
    }

    auto Triangle::GetIncircle           () const noexcept -> Circle
    {
        const auto& a = GetSideLengthA();
        const auto& b = GetSideLengthB();
        const auto& c = GetSideLengthC();
        const auto& perimeter = S_Perimeter<>(a, b, c);

        const auto& incenter = ((m_va_ * a) + (m_vb_ * b) + (m_vc_ * c)) / perimeter;
        const auto& radius = GetArea() / (perimeter * 0.5F);

        return Circle(incenter, radius);
    }
    auto Triangle::GetCircumcircle       () const noexcept -> Circle
    {
        const auto& a = GetSideLengthA();
        const auto& b = GetSideLengthB();
        const auto& c = GetSideLengthC();

        const auto& aSq = math::Square<>(a);
        const auto& bSq = math::Square<>(b);
        const auto& cSq = math::Square<>(c);

        const auto& alpha = aSq * (bSq + cSq - aSq);
        const auto& beta = bSq * (aSq + cSq - bSq);
        const auto& gamma = cSq * (aSq + bSq - cSq);

        const auto& center = ((m_va_ * alpha) + (m_vb_ * beta) + (m_vc_ * gamma)) / (alpha + beta + gamma);

        const auto& area = GetArea();
        const auto& radius = (a * b * c) / (4.0F * area);

        return Circle(center, radius);
    }

    auto Triangle::IsEquilateral         (const float& epsilon) const noexcept -> bool
    {
        const auto& a = GetSideLengthA();
        const auto& b = GetSideLengthB();
        const auto& c = GetSideLengthC();

        return (std::abs(a - b) <= epsilon) and (std::abs(b - c) <= epsilon);
    }
    auto Triangle::IsIsosceles           (const float& epsilon) const noexcept -> bool
    {
        const auto& a = GetSideLengthA();
        const auto& b = GetSideLengthB();
        const auto& c = GetSideLengthC();

        return (std::abs(a - b) <= epsilon) or (std::abs(b - c) <= epsilon) or (std::abs(a - c) <= epsilon);
    }
    auto Triangle::IsScalene             (const float& epsilon) const noexcept -> bool
    {
        return not IsIsosceles(epsilon);
    }
    auto Triangle::IsRightAngle          (const float& epsilon) const noexcept -> bool
    {
        std::array sides = { GetSideLengthA(), GetSideLengthB(), GetSideLengthC() };

        std::ranges::sort(sides);

        const auto& aSq_plus_bSq = math::Square<>(sides[0]) + math::Square<>(sides[1]);
        const auto& cSq = math::Square<>(sides[2]);

        return std::abs(aSq_plus_bSq - cSq) <= epsilon;
    }

    void Triangle::TranslateBy           (const DirectX::XMVECTOR& v) noexcept
    {
        m_va_ += v;
        m_vb_ += v;
        m_vc_ += v;
    }

    auto Triangle::Distance_CentroidToCentroid                 (const Triangle& other) const noexcept -> float
    {
        return Distance4(GetCentroid(), other.GetCentroid());
    }
    auto Triangle::Distance_CentroidToCircumcircleEdge         (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - other.GetCircumcircleRadius();
    }
    auto Triangle::Distance_CentroidToIncircleEdge             (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - other.GetIncircleRadius();
    }
    auto Triangle::Distance_CircumcircleEdgeToCentroid         (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - GetCircumcircleRadius();
    }
    auto Triangle::Distance_CircumcircleEdgeToCircumcircleEdge (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - (GetCircumcircleRadius() + other.GetCircumcircleRadius());
    }
    auto Triangle::Distance_CircumcircleEdgeToIncircleEdge     (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - (GetCircumcircleRadius() + other.GetIncircleRadius());
    }
    auto Triangle::Distance_IncircleEdgeToCentroid             (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - GetIncircleRadius();
    }
    auto Triangle::Distance_IncircleEdgeToIncircleEdge         (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - (GetIncircleRadius() + other.GetIncircleRadius());
    }
    auto Triangle::Distance_IncircleEdgeToCircumcircleEdge     (const Triangle& other) const noexcept -> float
    {
        return Distance_CentroidToCentroid(other) - (GetIncircleRadius() + other.GetCircumcircleRadius());
    }

    auto Triangle::Distance_CentroidToCenter                   (const Circle& circle) const noexcept -> float
    {
        return Distance4(GetCentroid(), circle.GetCenter());
    }
    auto Triangle::Distance_CentroidToEdge                     (const Circle& circle) const noexcept -> float
    {
        return Distance_CentroidToCenter(circle) - circle.GetRadius();
    }
    auto Triangle::Distance_CircumcircleEdgeToCenter           (const Circle& circle) const noexcept -> float
    {
        return Distance_CentroidToCenter(circle) - GetCircumcircleRadius();
    }
    auto Triangle::Distance_CircumcircleEdgeToEdge             (const Circle& circle) const noexcept -> float
    {
        return Distance_CentroidToCenter(circle) - (GetCircumcircleRadius() + circle.GetRadius());
    }
    auto Triangle::Distance_IncircleEdgeToCenter               (const Circle& circle) const noexcept -> float
    {
        return Distance_CentroidToCenter(circle) - GetIncircleRadius();
    }
    auto Triangle::Distance_IncircleEdgeToEdge                 (const Circle& circle) const noexcept -> float
    {
        return Distance_CentroidToCenter(circle) - (GetIncircleRadius() + circle.GetRadius());
    }
}

#endif
