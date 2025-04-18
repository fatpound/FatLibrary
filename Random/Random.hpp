#pragma once

#include <FatNamespaces.hpp>

#include <Math/Numbers/Primes.hpp>

#include <random>
#include <concepts>

namespace fatpound::random
{
    template <::std::unsigned_integral N>
    auto RandomPrime(const N& min, const N& max) -> N
    {
        ::std::minstd_rand rng{ ::std::random_device{}() };
        const auto& rand_num = ::std::uniform_int_distribution<N>{ min, max }(rng);

        if (FATSPACE_NUMBERS::IsPrime<>(rand_num))
        {
            return rand_num;
        }

        if (const auto& next = FATSPACE_NUMBERS::NextPrime<>(rand_num); next <= max)
        {
            return next;
        }

        if (const auto& prev = FATSPACE_NUMBERS::PrevPrime<>(rand_num); min <= prev)
        {
            return prev;
        }

        return 0;
    }

    template <::std::unsigned_integral N = ::std::size_t>
    auto RollDice() -> N
    {
        ::std::minstd_rand rng{ ::std::random_device{}() };

        return static_cast<N>(::std::uniform_int_distribution<::std::size_t>{ 1U, 6U }(rng));
    }

    template <::std::unsigned_integral N = ::std::size_t>
    auto RandUInt(
        const N& min = ::std::numeric_limits<N>::min(),
        const N& max = ::std::numeric_limits<N>::max()) -> N
    {
        ::std::minstd_rand rng{ ::std::random_device{}() };

        return static_cast<N>(::std::uniform_int_distribution<::std::size_t>{ min, max }(rng));
    }

    template <::std::floating_point N = float>
    auto RandFloat(
        const N& min = ::std::numeric_limits<N>::min(),
        const N& max = ::std::numeric_limits<N>::max()) -> N
    {
        ::std::minstd_rand rng{ ::std::random_device{}() };

        return static_cast<N>(::std::uniform_real_distribution<long double>{ min, max }(rng));
    }
}
