#pragma once

#include <cstdint>

#include <type_traits>
#include <queue>
#include <bitset>
#include <limits>
#include <mutex>
#include <atomic>
#include <optional>

namespace fatpound::io
{
    class Keyboard final
    {
        static constexpr auto scx_bufferSize_ = 16U;

    public:
        struct alignas(2) KeyEvent
        {
            enum struct Type : std::uint8_t
            {
                Press,
                Release,

                Invalid
            };

            Type                           type{ Type::Invalid };
            std::underlying_type_t<Type>   code{};
        };


    public:
        using Char_t    = unsigned char;
        using KeyCode_t = decltype(KeyEvent::code);


    public:
        explicit Keyboard()                    = default;
        explicit Keyboard(const Keyboard&)     = delete;
        explicit Keyboard(Keyboard&&) noexcept = delete;

        auto operator = (const Keyboard&)     -> Keyboard& = delete;
        auto operator = (Keyboard&&) noexcept -> Keyboard& = delete;
        ~Keyboard() noexcept                               = default;


    public:
        auto GetEvent() noexcept -> std::optional<KeyEvent>;
        auto GetChar()  noexcept -> std::optional<unsigned char>;

        [[nodiscard]] auto KeyIsPressed(KeyCode_t code) const noexcept -> bool;
        [[nodiscard]] auto AutoRepeatIsEnabled() const noexcept -> bool;
        [[nodiscard]] auto KeyBufferIsEmpty()  const noexcept -> bool;
        [[nodiscard]] auto CharBufferIsEmpty() const noexcept -> bool;

        void EnableAutoRepeat()    noexcept;
        void DisableAutoRepeat()   noexcept;
        void ClearKeyStateBitset() noexcept;

        void AddKeyPressEvent(unsigned char keycode);
        void AddKeyReleaseEvent(unsigned char keycode);
        void AddChar(unsigned char ch);


    protected:


    private:
        template <typename U>
        static void TrimBuffer_NoGuard_(std::queue<U>& buffer) noexcept
        {
            while (buffer.size() > scx_bufferSize_)
            {
                buffer.pop();
            }
        }


    private:
        std::queue<KeyEvent>                                 m_key_event_queue_;
        std::queue<unsigned char>                            m_char_buffer_;

        std::bitset<std::numeric_limits<KeyCode_t>::max()>   m_key_states_;

        std::atomic_bool                                     m_auto_repeat_enabled_;
        mutable std::mutex                                   m_mtx_;
    };

    using KeyEvent = Keyboard::KeyEvent;
}
