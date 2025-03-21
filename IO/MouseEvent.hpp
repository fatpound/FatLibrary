#pragma once

#include <cstdint>

namespace fatpound::io
{
    struct alignas(16) MouseEvent final
    {
        enum struct Type : ::std::uint8_t
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

        Type type{ Type::Invalid };

        bool left_is_pressed{};
        bool right_is_pressed{};
        bool wheel_is_pressed{};

        // ints are below for alignment

        int pos_x{};
        int pos_y{};
        int wheel_delta_carry{};
    };
}
