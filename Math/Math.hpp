#pragma once

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include <DirectXMath.h>
#endif

#include "Numbers/Numbers.hpp"

#include "AngularConv.hpp"
#include "Common.hpp"
#include "Geometry.hpp"
#include "Multiplicative.hpp"
#include "Rect.hpp"

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)

namespace fatpound::math
{
    static auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR
    {
        return ::DirectX::XMVectorSubtract(pos1_vec, pos2_vec);
    }

    static auto GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept -> float
    {
        return ::DirectX::XMVectorGetX(
            ::DirectX::XMVector2Length(
                ::DirectX::XMVectorSubtract(
                    ::DirectX::XMLoadFloat2(&pos1),
                    ::DirectX::XMLoadFloat2(&pos2)
                )
            )
        );
    }
    static auto GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept -> float
    {
        return ::DirectX::XMVectorGetX(
            ::DirectX::XMVector3Length(
                GetDifferenceVector(
                    ::DirectX::XMLoadFloat3(&pos1),
                    ::DirectX::XMLoadFloat3(&pos2)
                )
            )
        );
    }
}

#endif
