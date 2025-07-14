#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/Compiler.hpp>
#include <_macros/Namespaces.hpp>

#include <Win32_/include/WinAPI.hpp>
#include <d2d1.h>
#include <wrl.h>

#include <DirectXMath.h>

#include <Traits/include/Bitwise.hpp>
#include <Utility/Gfx/include/SizePack.hpp>

#include <cstddef>

#include <vector>
#include <stdexcept>

#pragma comment(lib, "d2d1")

namespace fatpound::win32::d2d
{
    /// @brief The Graphics class provides a wrapper for Direct2D rendering operations on a window, including drawing lines and polylines, clearing the screen, and managing the drawing frame lifecycle
    ///
    class Graphics final
    {
    public:
        using Color_t = D2D1_COLOR_F;
        using Point_t = D2D1_POINT_2F;
        

    public:
        explicit Graphics(const HWND& hWnd, const FATSPACE_UTILITY_GFX::SizePack& dimensions);

        explicit Graphics()                    = delete;
        explicit Graphics(const Graphics&)     = delete;
        explicit Graphics(Graphics&&) noexcept = delete;

        auto operator = (const Graphics&)     -> Graphics& = delete;
        auto operator = (Graphics&&) noexcept -> Graphics& = delete;
        ~Graphics() noexcept                               = default;


    public:
        template <traits::IntegralOrFloating T> FATLIB_FORCEINLINE constexpr auto GetWidth()  const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_width);
        }
        template <traits::IntegralOrFloating T> FATLIB_FORCEINLINE constexpr auto GetHeight() const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_height);
        }

        template <bool Clear = true>
        void BeginFrame() noexcept
        {
            m_pRenderTarget_->BeginDraw();

            if constexpr (Clear)
            {
                ClearScreen<>();
            }
        }

        template <float r = 0.0F, float g = 0.0F, float b = 0.0F>
        void ClearScreen() noexcept
        {
            m_pRenderTarget_->Clear(D2D1::ColorF(r, g, b));
        }


    public:
        void ClearScreen(const float& r, const float& g, const float& b) noexcept;

        void DrawLine(const Point_t& p0, const Point_t& p1) noexcept;
        void DrawLine(const Point_t& p0, const Point_t& p1, const Color_t& color) noexcept;
        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F& color) noexcept;
        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F& color, const DirectX::XMMATRIX& transform) noexcept;

        void EndFrame() noexcept;


    protected:
        
        
    private:
        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>   m_pRenderTarget_;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>    m_pBrush_;

        const FATSPACE_UTILITY_GFX::SizePack            mc_dimensions_;
    };
}

#endif
