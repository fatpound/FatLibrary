#include <IO/Mouse.hpp>

namespace fatpound::io
{
    auto Mouse::GetEvent() noexcept -> std::optional<Event>
    {
        if (EventBufferIsEmpty())
        {
            return std::nullopt;
        }

        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        auto mouseE = m_event_buffer_.front();
        m_event_buffer_.pop();

        return mouseE;
    }

    auto Mouse::GetPos() const noexcept -> std::pair<Position_t, Position_t>
    {
        return { GetPosX(), GetPosY() };
    }
    auto Mouse::GetPosX() const noexcept -> Position_t
    {
        return m_pos_x_;
    }
    auto Mouse::GetPosY() const noexcept -> Position_t
    {
        return m_pos_y_;
    }

    auto Mouse::EventBufferIsEmpty() const noexcept -> bool
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        return m_event_buffer_.empty();
    }
    auto Mouse::IsInWindow() const noexcept -> bool
    {
        return m_is_in_window_;
    }

    auto Mouse::LeftIsPressed() const noexcept -> bool
    {
        return m_left_is_pressed_;
    }
    auto Mouse::RightIsPressed() const noexcept -> bool
    {
        return m_right_is_pressed_;
    }
    auto Mouse::WheelIsPressed() const noexcept -> bool
    {
        return m_wheel_is_pressed_;
    }

    void Mouse::AddMouseMoveEvent(const int& x, const int& y)
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_pos_x_ = x;
        m_pos_y_ = y;

        m_event_buffer_.push(Event{ .type = Event::Type::Move, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddMouseEnterEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_is_in_window_ = true;

        m_event_buffer_.push(Event{ .type = Event::Type::Enter });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddMouseLeaveEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_is_in_window_ = false;

        m_event_buffer_.push(Event{ .type = Event::Type::Leave });

        TrimBuffer_NoGuard_();
    }

    void Mouse::AddLeftPressEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_left_is_pressed_ = true;

        m_event_buffer_.push(Event{ .type = Event::Type::LPress, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddLeftReleaseEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_left_is_pressed_ = false;

        m_event_buffer_.push(Event{ .type = Event::Type::LRelease });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddRightPressEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_right_is_pressed_ = true;

        m_event_buffer_.push(Event{ .type = Event::Type::RPress });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddRightReleaseEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_right_is_pressed_ = false;

        m_event_buffer_.push(Event{ .type = Event::Type::RRelease });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddWheelPressEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_wheel_is_pressed_ = true;

        m_event_buffer_.push(Event{ .type = Event::Type::WheelPress });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddWheelReleaseEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_wheel_is_pressed_ = false;

        m_event_buffer_.push(Event{ .type = Event::Type::WheelRelease });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddWheelUpEvent_NoGuard()
    {
        m_event_buffer_.push(Event{ .type = Event::Type::WheelUp });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddWheelDownEvent_NoGuard()
    {
        m_event_buffer_.push(Event{ .type = Event::Type::WheelDown });

        TrimBuffer_NoGuard_();
    }
    void Mouse::AddWheelUpEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        AddWheelUpEvent_NoGuard();
    }
    void Mouse::AddWheelDownEvent()
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        AddWheelDownEvent_NoGuard();
    }

    void Mouse::ProcessWheelDelta(const WheelDelta_t& delta)
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_wheel_delta_carry_ += delta;

        // NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define FATLIB_WHEEL_DELTA 120
        while (m_wheel_delta_carry_ >= FATLIB_WHEEL_DELTA)
        {
            m_wheel_delta_carry_ -= FATLIB_WHEEL_DELTA;

            AddWheelUpEvent_NoGuard();
        }

        while (m_wheel_delta_carry_ <= -FATLIB_WHEEL_DELTA)
        {
            m_wheel_delta_carry_ += FATLIB_WHEEL_DELTA;

            AddWheelDownEvent_NoGuard();
        }
#undef FATLIB_WHEEL_DELTA
        // NOLINTEND(cppcoreguidelines-macro-usage)
    }

    void Mouse::TrimBuffer_NoGuard_() noexcept
    {
        while (m_event_buffer_.size() > scx_bufferSize_)
        {
            m_event_buffer_.pop();
        }
    }
}
