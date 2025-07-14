#include <Utility/ViewXM.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::utility
{
    auto ViewXM::GetCameraXM     () const noexcept -> DirectX::XMMATRIX
    {
        return m_camera_;
    }
    auto ViewXM::GetProjectionXM () const noexcept -> DirectX::XMMATRIX
    {
        return m_projection_;
    }

    void ViewXM::SetCameraXM     (const DirectX::XMMATRIX&     camera) noexcept
    {
        m_camera_ = camera;
    }
    void ViewXM::SetProjectionXM (const DirectX::XMMATRIX& projection) noexcept
    {
        m_projection_ = projection;
    }
}

#endif
