#pragma once

#include <_macros/STL.hpp>

#include "AngularConv.hpp"

#include <cmath>
#include <concepts>

namespace fatpound::geometry
{
    template <std::floating_point T = float, std::convertible_to<T> U> inline CX_MATH26 auto CalculateYaw_Rad   (const U& fwd, const U& hrz) noexcept -> T
    {
        return static_cast<T>(std::atan2(hrz, fwd));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> inline CX_MATH26 auto CalculatePitch_Rad (const U& fwd, const U& vrt) noexcept -> T
    {
        return static_cast<T>(std::atan2(vrt, fwd));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> inline CX_MATH26 auto CalculateRoll_Rad  (const U& hrz, const U& vrt) noexcept -> T
    {
        return static_cast<T>(std::atan2(vrt, hrz));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> inline CX_MATH26 auto CalculateYaw_Deg   (const U& fwd, const U& hrz) noexcept -> T
    {
        return RadToDeg<T>(CalculateYaw_Rad<T>(fwd, hrz));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> inline CX_MATH26 auto CalculatePitch_Deg (const U& fwd, const U& vrt) noexcept -> T
    {
        return RadToDeg<T>(CalculatePitch_Rad<T>(fwd, vrt));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> inline CX_MATH26 auto CalculateRoll_Deg  (const U& hrz, const U& vrt) noexcept -> T
    {
        return RadToDeg<T>(CalculateRoll_Rad<T>(hrz, vrt));
    }
}
