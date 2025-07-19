#include "Keyboard.hpp"

namespace fatpound::io
{
    auto Keyboard::GetEvent() noexcept -> std::optional<KeyEvent>
    {
        if (KeyBufferIsEmpty())
        {
            return std::nullopt;
        }

        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        auto keyE = m_key_event_queue_.front();
        m_key_event_queue_.pop();

        return keyE;
    }
    auto Keyboard::GetChar() noexcept -> std::optional<unsigned char>
    {
        if (CharBufferIsEmpty())
        {
            return std::nullopt;
        }

        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        auto ch = m_char_buffer_.front();
        m_char_buffer_.pop();

        return ch;
    }

    auto Keyboard::KeyIsPressed(KeyCode_t code) const noexcept -> bool
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        return m_key_states_[code];
    }
    auto Keyboard::AutoRepeatIsEnabled() const noexcept -> bool
    {
        return m_auto_repeat_enabled_;
    }
    auto Keyboard::KeyBufferIsEmpty() const noexcept -> bool
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        return m_key_event_queue_.empty();
    }
    auto Keyboard::CharBufferIsEmpty() const noexcept -> bool
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        return m_char_buffer_.empty();
    }

    void Keyboard::EnableAutoRepeat() noexcept
    {
        m_auto_repeat_enabled_ = true;
    }
    void Keyboard::DisableAutoRepeat() noexcept
    {
        m_auto_repeat_enabled_ = false;
    }
    void Keyboard::ClearKeyStateBitset() noexcept
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_key_states_.reset();
    }

    void Keyboard::AddKeyPressEvent(unsigned char keycode)
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_key_states_[keycode] = true;

        m_key_event_queue_.push(KeyEvent{ .type = KeyEvent::Type::Press, .code = keycode });

        S_TrimBuffer_NoGuard_(m_key_event_queue_);
    }
    void Keyboard::AddKeyReleaseEvent(unsigned char keycode)
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_key_states_[keycode] = false;

        m_key_event_queue_.push(KeyEvent{ .type = KeyEvent::Type::Release, .code = keycode });

        S_TrimBuffer_NoGuard_(m_key_event_queue_);
    }
    void Keyboard::AddChar(unsigned char ch)
    {
        const std::lock_guard<std::mutex> guard{ m_mtx_ };

        m_char_buffer_.push(ch);

        S_TrimBuffer_NoGuard_(m_char_buffer_);
    }
}
