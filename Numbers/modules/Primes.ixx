module;

#include "Primes.hpp"

export module FatPound.Numbers.Primes;

export namespace fatpound::numbers
{
    using numbers::IsPrime_GT4;
    using numbers::IsPrime;
    using numbers::PrevPrime_GT5;
    using numbers::PrevPrime;
    using numbers::NextPrime_GT4;
    using numbers::NextPrime;
    using numbers::ClosestPrime_GT5;
    using numbers::ClosestPrime;
    using numbers::NthPrime_GT2;
    using numbers::NthPrime;
    using numbers::NthSuperPrime_GT2;
    using numbers::NthSuperPrime;
    using numbers::IsStrongPrime_GT10;
    using numbers::IsStrongPrime;
}

// module : private;
