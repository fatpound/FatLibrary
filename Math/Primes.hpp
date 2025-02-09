#pragma once

#include <concepts>

namespace fatpound::math
{
    template <std::signed_integral N> static constexpr auto IsPrime  (const N& num) -> bool
    {
        if (num < 4)
        {
            return num > 1;
        }

        if (num % 2 == 0 or num % 3 == 0)
        {
            return false;
        }

        const N m = num + 1;

        for (N i = 5; (i * i) < m; i += 6)
        {
            if ((num % i == 0) or (num % (i + 2) == 0))
            {
                return false;
            }
        }

        return true;
    }
    template <std::signed_integral N> static constexpr auto NextPrime(const N& num) -> N
    {
        if (num % 2 == 0)
        {
            ++num;
        }

        while (not IsPrime<>(num))
        {
            num += 2;
        }

        return num;
    }
    template <std::signed_integral N> static constexpr auto PrevPrime(const N& num) -> N
    {
        if (num % 2 == 0)
        {
            --num;
        }

        while (not IsPrime<>(num))
        {
            num -= 2;
        }

        return num;
    }
    template <std::signed_integral N> static constexpr auto NthPrime (const N& num) -> N
    {
        if (num == 1)
        {
            return 2;
        }

        N i = 3;
        N counter = 1;

        while (true)
        {
            if (IsPrime<>(i))
            {
                ++counter;

                if (counter == num)
                {
                    break;
                }
            }

            i += 2;
        }

        return i;
    }
}