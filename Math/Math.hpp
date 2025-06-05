#pragma once

#ifdef _MSC_VER
    #include <DirectXMath.h>
#endif

#include <Math/Numbers/Numbers.hpp>
#include <Math/Geometry/Geometry.hpp>

#include <Math/Common.hpp>
#include <Math/Multiplicative.hpp>

#ifdef _MSC_VER

namespace fatpound::math
{
    static auto operator - (const DirectX::XMVECTOR& pos1_vec, const DirectX::XMVECTOR& pos2_vec) noexcept -> DirectX::XMVECTOR
    {
        return DirectX::XMVectorSubtract(pos1_vec, pos2_vec);
    }
    static auto operator - (const DirectX::XMFLOAT2& pos1, const DirectX::XMFLOAT2& pos2) noexcept -> float
    {
        return DirectX::XMVectorGetX(DirectX::XMVector2Length(DirectX::XMLoadFloat2(&pos1) - DirectX::XMLoadFloat2(&pos2)));
    }
    static auto operator - (const DirectX::XMFLOAT3& pos1, const DirectX::XMFLOAT3& pos2) noexcept -> float
    {
        return DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMLoadFloat3(&pos1) - DirectX::XMLoadFloat3(&pos2)));
    }
}

#endif
