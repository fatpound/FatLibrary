#pragma once

#include <cstdint>

#include <queue>
#include <utility>
#include <mutex>
#include <atomic>
#include <optional>

namespace fatpound::io
{
    class Mouse final
    {
        static constexpr auto scx_bufferSize_ = 16U;

    public:
        struct alignas(16) Event
        {
            enum struct Type : std::uint8_t
            {
                Move,

                LPress,
                LRelease,
                RPress,
                RRelease,
                WheelPress,
                WheelRelease,

                WheelUp,
                WheelDown,
                WheelDelta,

                Enter,
                Leave,

                Invalid
            };

            Type   type{ Type::Invalid };

            bool   left_is_pressed{};
            bool   right_is_pressed{};
            bool   wheel_is_pressed{};

            int    pos_x{};
            int    pos_y{};
            int    wheel_delta_carry{};

            // ints are below bool members for alignment
        };


    public:
        using   Position_t = decltype(Event::pos_x);
        using WheelDelta_t = decltype(Event::wheel_delta_carry);


    public:
        explicit Mouse()                 = default;
        explicit Mouse(const Mouse&)     = delete;
        explicit Mouse(Mouse&&) noexcept = delete;

        auto operator = (const Mouse&)     -> Mouse& = delete;
        auto operator = (Mouse&&) noexcept -> Mouse& = delete;
        ~Mouse() noexcept                            = default;


    public:
        auto GetEvent() noexcept -> std::optional<Event>;

        [[nodiscard]] auto GetPos() const noexcept -> std::pair<Position_t, Position_t>;
        [[nodiscard]] auto GetPosX() const noexcept -> Position_t;
        [[nodiscard]] auto GetPosY() const noexcept -> Position_t;

        [[nodiscard]] auto EventBufferIsEmpty() const noexcept -> bool;
        [[nodiscard]] auto IsInWindow() const noexcept -> bool;

        [[nodiscard]] auto LeftIsPressed()  const noexcept -> bool;
        [[nodiscard]] auto RightIsPressed() const noexcept -> bool;
        [[nodiscard]] auto WheelIsPressed() const noexcept -> bool;

        void AddMouseMoveEvent(const int x, const int y);
        void AddMouseEnterEvent();
        void AddMouseLeaveEvent();

        void AddLeftPressEvent         ();
        void AddLeftReleaseEvent       ();
        void AddRightPressEvent        ();
        void AddRightReleaseEvent      ();
        void AddWheelPressEvent        ();
        void AddWheelReleaseEvent      ();
        void AddWheelUpEvent_NoGuard   ();
        void AddWheelDownEvent_NoGuard ();
        void AddWheelUpEvent           ();
        void AddWheelDownEvent         ();

        void ProcessWheelDelta(const WheelDelta_t delta);


    protected:


    private:
        void TrimBuffer_NoGuard_() noexcept;


    private:
        std::queue<Event>    m_event_buffer_;

        mutable std::mutex   m_mtx_;

        Position_t           m_pos_x_{};
        Position_t           m_pos_y_{};

        WheelDelta_t         m_wheel_delta_carry_{};

        std::atomic_bool     m_is_in_window_;
        std::atomic_bool     m_left_is_pressed_;
        std::atomic_bool     m_right_is_pressed_;
        std::atomic_bool     m_wheel_is_pressed_;
    };

    using MouseEvent = Mouse::Event;
}
