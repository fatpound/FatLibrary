#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <DirectXMath.h>

namespace fatpound::math::geometry
{
    static auto operator +       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorAdd(p0, p1);
    }
    static auto operator -       (const DirectX::XMVECTOR& p1, const DirectX::XMVECTOR& p0) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorSubtract(p1, p0);
    }
    static auto operator *       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorMultiply(p0, p1);
    }
    static auto operator /       (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorDivide(p0, p1);
    }

    static auto operator *       (const float& scale, const DirectX::XMVECTOR& v) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorScale(v, scale);
    }
    static auto operator *       (const DirectX::XMVECTOR& v, const float& scale) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorScale(v, scale);
    }
    static auto operator /       (const DirectX::XMVECTOR& v, const float& scale) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorScale(v, 1.0F / scale);
    }

    static auto CompareDistance2 (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return DirectX::XMVectorGetX(DirectX::XMVector2LengthSq(p0)) > DirectX::XMVectorGetX(DirectX::XMVector2LengthSq(p1));
    }
    static auto CompareDistance  (const DirectX::XMFLOAT2& p0, const DirectX::XMFLOAT2& p1) noexcept -> float
    {
        return CompareDistance2(DirectX::XMLoadFloat2(&p0), DirectX::XMLoadFloat2(&p1));
    }

    static auto DistanceVector2  (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVector2Length(p1 - p0);
    }
    static auto DistanceVector3  (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVector3Length(p1 - p0);
    }
    static auto DistanceVector4  (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVector4Length(p1 - p0);
    }
    static auto Distance2        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return DirectX::XMVectorGetX(DistanceVector2(p0, p1));
    }
    static auto Distance3        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return DirectX::XMVectorGetX(DistanceVector3(p0, p1));
    }
    static auto Distance4        (const DirectX::XMVECTOR& p0, const DirectX::XMVECTOR& p1) noexcept -> float
    {
        return DirectX::XMVectorGetX(DistanceVector4(p0, p1));
    }
    static auto Distance         (const DirectX::XMFLOAT2& p0, const DirectX::XMFLOAT2& p1) noexcept -> float
    {
        return Distance2(DirectX::XMLoadFloat2(&p0), DirectX::XMLoadFloat2(&p1));
    }
    static auto Distance         (const DirectX::XMFLOAT3& p0, const DirectX::XMFLOAT3& p1) noexcept -> float
    {
        return Distance3(DirectX::XMLoadFloat3(&p0), DirectX::XMLoadFloat3(&p1));
    }
    static auto Distance         (const DirectX::XMFLOAT4& p0, const DirectX::XMFLOAT4& p1) noexcept -> float
    {
        return Distance4(DirectX::XMLoadFloat4(&p0), DirectX::XMLoadFloat4(&p1));
    }
}

#endif
