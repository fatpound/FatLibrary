#pragma once

#include <cstddef>

#include <vector>
#include <random>

namespace fatpound::random
{
    /// @brief URand is a functor that generates a random permutation of unique indices in the range [0, count).
    ///        Each call to operator() returns the next unique random index, or -1 if all indices have been used
    /// 
    class URand final
    {
    public:
        URand(const std::size_t& count);

        URand()                 = delete;
        URand(const URand&)     = delete;
        URand(URand&&) noexcept = delete;

        auto operator = (const URand&)     -> URand& = delete;
        auto operator = (URand&&) noexcept -> URand& = delete;
        ~URand() noexcept                            = default;


    public:
        auto operator () () -> std::ptrdiff_t;


    protected:


    private:
        std::vector<std::size_t>                     m_vec_;
        std::minstd_rand                             m_rng_;
        std::uniform_int_distribution<std::size_t>   m_dist_;

        std::size_t                                  m_current_;
    };

    using UniqueRand = URand;
}