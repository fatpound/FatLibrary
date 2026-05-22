#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/STL.hpp>

#include <Geometry/Shape/include/Circle.hpp>
#include <Traits/include/Bitwise.hpp>

#include <DirectXMath.h>

#include <cstdlib>
#include <cmath>

namespace fatpound::geometry::shape
{
    class alignas(32) Triangle
    {
        static constexpr auto scx_Default_Z_ = 1.0F;
        static constexpr auto scx_Default_W_ = 1.0F;

    public:
        explicit Triangle(const DirectX::XMVECTOR& va, const DirectX::XMVECTOR& vb, const DirectX::XMVECTOR& vc);

        explicit Triangle() noexcept  = delete;
        Triangle(const Triangle&)     = default;
        Triangle(Triangle&&) noexcept = default;

        auto operator = (const Triangle&)     -> Triangle& = default;
        auto operator = (Triangle&&) noexcept -> Triangle& = default;
        ~Triangle() noexcept                               = default;
            

    public:
        template <traits::UIntegralOrFloating T> static constexpr auto S_IsValid   (const T& a, const T& b, const T& c) noexcept -> bool
        {
            return     ((std::abs(b - c) < a) and (a < (b + c)))
                   and ((std::abs(a - c) < b) and (b < (a + c)))
                   and ((std::abs(a - b) < c) and (c < (a + b)));
        }
        template <traits::UIntegralOrFloating T> static constexpr auto S_Perimeter (const T& a, const T& b, const T& c) noexcept -> T
        {
            return a + b + c;
        }
        template <traits::UIntegralOrFloating T> static CX_MATH26 auto S_Area      (const T& a, const T& b, const T& c) noexcept -> T
        {
            const auto s = S_Perimeter<>(a, b, c) / static_cast<T>(2);

            return std::sqrt(s * (s - a) * (s - b) * (s - c));
        }
        template <traits::UIntegralOrFloating T> static constexpr auto S_Area      (const T& height, const T& base) noexcept -> T
        {
            return (base * height) / static_cast<T>(2.0);
        }


    public:
        auto GetVertexA            () const noexcept -> DirectX::XMVECTOR;
        auto GetVertexB            () const noexcept -> DirectX::XMVECTOR;
        auto GetVertexC            () const noexcept -> DirectX::XMVECTOR;
        auto GetCentroid           () const noexcept -> DirectX::XMVECTOR;
        
        auto GetSideLengthA        () const noexcept -> float;
        auto GetSideLengthB        () const noexcept -> float;
        auto GetSideLengthC        () const noexcept -> float;

        auto GetArea               () const noexcept -> float;
        auto GetPerimeter          () const noexcept -> float;
        auto GetIncircleRadius     () const noexcept -> float;
        auto GetCircumcircleRadius () const noexcept -> float;

        auto GetIncircle           () const noexcept -> Circle;
        auto GetCircumcircle       () const noexcept -> Circle;
        
        auto IsEquilateral         (const float& epsilon = 0.001F) const noexcept -> bool;
        auto IsIsosceles           (const float& epsilon = 0.001F) const noexcept -> bool;
        auto IsScalene             (const float& epsilon = 0.001F) const noexcept -> bool;
        auto IsRightAngle          (const float& epsilon = 0.001F) const noexcept -> bool;
        
        void TranslateBy           (const DirectX::XMVECTOR& v) noexcept;

        auto Distance_CentroidToCentroid                 (const Triangle& other) const noexcept -> float;
        auto Distance_CentroidToCircumcircleEdge         (const Triangle& other) const noexcept -> float;
        auto Distance_CentroidToIncircleEdge             (const Triangle& other) const noexcept -> float;
        auto Distance_CircumcircleEdgeToCentroid         (const Triangle& other) const noexcept -> float;
        auto Distance_CircumcircleEdgeToCircumcircleEdge (const Triangle& other) const noexcept -> float;
        auto Distance_CircumcircleEdgeToIncircleEdge     (const Triangle& other) const noexcept -> float;
        auto Distance_IncircleEdgeToCentroid             (const Triangle& other) const noexcept -> float;
        auto Distance_IncircleEdgeToIncircleEdge         (const Triangle& other) const noexcept -> float;
        auto Distance_IncircleEdgeToCircumcircleEdge     (const Triangle& other) const noexcept -> float;

        auto Distance_CentroidToCenter                   (const Circle&  circle) const noexcept -> float;
        auto Distance_CentroidToEdge                     (const Circle&  circle) const noexcept -> float;
        auto Distance_CircumcircleEdgeToCenter           (const Circle&  circle) const noexcept -> float;
        auto Distance_CircumcircleEdgeToEdge             (const Circle&  circle) const noexcept -> float;
        auto Distance_IncircleEdgeToCenter               (const Circle&  circle) const noexcept -> float;
        auto Distance_IncircleEdgeToEdge                 (const Circle&  circle) const noexcept -> float;


    protected:


    private:
        DirectX::XMVECTOR   m_va_;
        DirectX::XMVECTOR   m_vb_;
        DirectX::XMVECTOR   m_vc_;
    };
}

#endif
