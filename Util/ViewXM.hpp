#pragma once

#if FAT_BUILDING_WITH_MSVC
#include <DirectXMath.h>

namespace fatpound::util
{
    class ViewXM final
    {
    public:
        explicit ViewXM()              = default;
        explicit ViewXM(const ViewXM&) = delete;
        explicit ViewXM(ViewXM&&)      = delete;

        auto operator = (const ViewXM&) -> ViewXM& = delete;
        auto operator = (ViewXM&&)      -> ViewXM& = delete;
        ~ViewXM() noexcept                         = default;


    public:
        [[nodiscard]] auto GetCameraXM()     const noexcept -> ::DirectX::XMMATRIX;
        [[nodiscard]] auto GetProjectionXM() const noexcept -> ::DirectX::XMMATRIX;

        void SetCameraXM(const ::DirectX::XMMATRIX& camera) noexcept;
        void SetProjectionXM(const ::DirectX::XMMATRIX& projection) noexcept;


    protected:


    private:
        ::DirectX::XMMATRIX m_camera_{};
        ::DirectX::XMMATRIX m_projection_{};
    };
}

#endif
