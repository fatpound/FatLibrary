#include "../include/Graphics.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace fatpound::win32::d2d
{
    Graphics::Graphics(const HWND& hWnd, const utility::SizePack& dimensions)
        :
        mc_dimensions_(dimensions)
    {
        Microsoft::WRL::ComPtr<ID2D1Factory> pFactory;

        if (FAILED(D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            throw std::runtime_error("A problem occured when creating the D2D1 factory!");
        }

        if (FAILED(pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(GetWidth<UINT32>(), GetHeight<UINT32>())),
            &m_pRenderTarget_)))
        {
            throw std::runtime_error("A problem occured when creating the HwndRenderTarget!");
        }
    }


    void Graphics::ClearScreen(const float& r, const float& g, const float& b) noexcept
    {
        m_pRenderTarget_->Clear(D2D1::ColorF(r, g, b));
    }

    void Graphics::DrawLine(const Point_t& p0, const Point_t& p1) noexcept
    {
        m_pRenderTarget_->DrawLine(p0, p1, m_pBrush_.Get());
    }
    void Graphics::DrawLine(const Point_t& p0, const Point_t& p1, const Color_t& color) noexcept
    {
        m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

        DrawLine(p0, p1);
    }
    void Graphics::DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F& color) noexcept
    {
        m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

        for (std::size_t i{}; i < vertices.size(); ++i)
        {
            const auto& current = vertices[i];
            const auto& next = vertices[(i + 1U) % vertices.size()];

            DrawLine(
                D2D1::Point2F(current.x, current.y),
                D2D1::Point2F(next.x, next.y)
            );
        }
    }
    void Graphics::DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F& color, const DirectX::XMMATRIX& transform) noexcept
    {
        m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

        for (std::size_t i = 1U; i < vertices.size() + 1U; ++i)
        {
            const auto& vec0 = DirectX::XMVector2TransformCoord(DirectX::XMLoadFloat2(&vertices[i - 1U]), transform);
            const auto& vec1 = DirectX::XMVector2TransformCoord(DirectX::XMLoadFloat2(&vertices[i % vertices.size()]), transform);

            DirectX::XMFLOAT2 transformed0;
            DirectX::XMFLOAT2 transformed1;
            DirectX::XMStoreFloat2(&transformed0, vec0);
            DirectX::XMStoreFloat2(&transformed1, vec1);

            DrawLine(
                D2D1::Point2F(transformed0.x, transformed0.y),
                D2D1::Point2F(transformed1.x, transformed1.y)
            );
        }
    }

    void Graphics::EndFrame() noexcept
    {
        m_pRenderTarget_->EndDraw();
    }
}

#endif
