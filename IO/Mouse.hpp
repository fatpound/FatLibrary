#pragma once

#include <FatNamespaces.hpp>

#if defined(_MSC_VER)
#include <FatWin32.hpp>
#else
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif
#endif

#include "MouseEvent.hpp"

#include <queue>
#include <utility>
#include <optional>

#if defined(_MSC_VER)
namespace fatpound::win32
{
    class WindowEx;
}
#endif

namespace fatpound::io
{
    class Mouse final
    {
#if defined(_MSC_VER)
        friend FATSPACE_WIN32::WindowEx;
#endif

        static constexpr auto scx_bufferSize_ = 16u;

    public:
        using pos_t = decltype(MouseEvent::pos_x);


    public:
        explicit Mouse()                 = default;
        explicit Mouse(const Mouse&)     = delete;
        explicit Mouse(Mouse&&) noexcept = delete;

        auto operator = (const Mouse&)     -> Mouse& = delete;
        auto operator = (Mouse&&) noexcept -> Mouse& = delete;
        ~Mouse() noexcept                            = default;


    public:
        auto GetEvent() noexcept -> std::optional<MouseEvent>
        {
            if (m_event_buffer_.empty())
            {
                return std::nullopt;
            }

            auto mouseE = m_event_buffer_.front();
            m_event_buffer_.pop();

            return mouseE;
        }

        auto GetPos() const noexcept -> std::pair<pos_t, pos_t>
        {
            return { m_pos_x_, m_pos_y_ };
        }

        auto GetPosX() const noexcept -> pos_t
        {
            return m_pos_x_;
        }
        auto GetPosY() const noexcept -> pos_t
        {
            return m_pos_y_;
        }

        auto EventBufferIsEmpty() const noexcept -> bool
        {
            return m_event_buffer_.empty();
        }

        auto IsInWindow() const noexcept -> bool
        {
            return m_is_in_window_;
        }

        auto LeftIsPressed()  const noexcept -> bool
        {
            return m_left_is_pressed_;
        }
        auto RightIsPressed() const noexcept -> bool
        {
            return m_right_is_pressed_;
        }
        auto WheelIsPressed() const noexcept -> bool
        {
            return m_wheel_is_pressed_;
        }


    protected:


    private:
        void OnMouseMove_(const int x, const int y)
        {
            m_pos_x_ = x;
            m_pos_y_ = y;

            m_event_buffer_.push(MouseEvent{ .type = MouseEvent::Type::Move, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

            TrimBuffer_();
        }
        void OnMouseEnter_()
        {
            m_is_in_window_ = true;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::Enter });

            TrimBuffer_();
        }
        void OnMouseLeave_()
        {
            m_is_in_window_ = false;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::Leave });

            TrimBuffer_();
        }

        void OnLeftPressed_()
        {
            m_left_is_pressed_ = true;

            m_event_buffer_.push(MouseEvent{ .type = MouseEvent::Type::LPress, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

            TrimBuffer_();
        }
        void OnLeftReleased_()
        {
            m_left_is_pressed_ = false;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::LRelease });

            TrimBuffer_();
        }
        void OnRightPressed_()
        {
            m_right_is_pressed_ = true;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::RPress });

            TrimBuffer_();
        }
        void OnRightReleased_()
        {
            m_right_is_pressed_ = false;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::RRelease });

            TrimBuffer_();
        }
        void OnWheelPressed_()
        {
            m_wheel_is_pressed_ = true;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::WheelPress });

            TrimBuffer_();
        }
        void OnWheelReleased_()
        {
            m_wheel_is_pressed_ = false;

            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::WheelRelease });

            TrimBuffer_();
        }
        void OnWheelUp_()
        {
            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::WheelUp });

            TrimBuffer_();
        }
        void OnWheelDown_()
        {
            m_event_buffer_.push(MouseEvent{ MouseEvent::Type::WheelDown });

            TrimBuffer_();
        }
        void OnWheelDelta_(const int delta)
        {
            m_wheel_delta_carry_ += delta;

            while (m_wheel_delta_carry_ >= WHEEL_DELTA)
            {
                m_wheel_delta_carry_ -= WHEEL_DELTA;

                OnWheelUp_();
            }

            while (m_wheel_delta_carry_ <= -WHEEL_DELTA)
            {
                m_wheel_delta_carry_ += WHEEL_DELTA;

                OnWheelDown_();
            }
        }

        void TrimBuffer_() noexcept
        {
            while (m_event_buffer_.size() > scx_bufferSize_)
            {
                m_event_buffer_.pop();
            }
        }


    private:
        std::queue<MouseEvent> m_event_buffer_;

        pos_t m_pos_x_{};
        pos_t m_pos_y_{};

        pos_t m_wheel_delta_carry_{};

        bool m_is_in_window_{};

        bool m_left_is_pressed_{};
        bool m_right_is_pressed_{};
        bool m_wheel_is_pressed_{};
    };
}
