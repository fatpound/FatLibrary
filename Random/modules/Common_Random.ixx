module;

#include "../include/Common.hpp"

export module FatPound.Random.Common;

export namespace fatpound
{
    using random::StdUniformDist;
    using random::StdOtherBernoulliDist;
    using random::StdPoissonDist;
    using random::StdNormalDist;
    using random::StdSamplingDist;
    using random::StdUniformOrNormalDist;
    using random::StdDistNoBernoulli;

    using random::RandPrimeNumber;
    using random::RandColor;
    using random::RandColorString;
    using random::RandString;
    using random::RandPassword;
}

// module : private;
