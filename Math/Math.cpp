#include "Math.hpp"

namespace dx = DirectX;

namespace fatpound::math
{
    auto GetDifferenceVector(const ::dx::XMVECTOR pos1_vec, const ::dx::XMVECTOR pos2_vec) noexcept -> ::dx::XMVECTOR
    {
        return ::dx::XMVectorSubtract(pos1_vec, pos2_vec);
    }

    auto GetDistanceBetweenXMF2(const ::dx::XMFLOAT2& pos1, const ::dx::XMFLOAT2& pos2) noexcept -> float
    {
        const auto& pos1Vec = ::dx::XMLoadFloat2(&pos1);
        const auto& pos2Vec = ::dx::XMLoadFloat2(&pos2);

        const auto& differenceVec = ::dx::XMVectorSubtract(pos1Vec, pos2Vec);

        return ::dx::XMVectorGetX(
            ::dx::XMVector2Length(differenceVec)
        );
    }
    auto GetDistanceBetweenXMF3(const ::dx::XMFLOAT3& pos1, const ::dx::XMFLOAT3& pos2) noexcept -> float
    {
        const auto& pos1Vec = ::dx::XMLoadFloat3(&pos1);
        const auto& pos2Vec = ::dx::XMLoadFloat3(&pos2);

        return ::dx::XMVectorGetX(
            ::dx::XMVector3Length(GetDifferenceVector(pos1Vec, pos2Vec))
        );
    }
}