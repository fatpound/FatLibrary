#include "URand.hpp"

#include <cassert>

#include <utility>
#include <numeric>

namespace fatpound::random
{
    URand::URand(const std::size_t& count)
        :
        m_vec_((assert(count > 0), count)),
        m_rng_(std::random_device{}()),
        m_dist_(0ULL, count - 1ULL),
        m_current_(0ULL)
    {
#if __cplusplus >= 202302L
        std::ranges::iota(m_vec_, 0ULL);
#else
        std::iota<>(m_vec_.begin(), m_vec_.end(), 0ULL);
#endif
    }

    auto URand::operator () () -> std::ptrdiff_t
    {
        if (m_current_ >= m_vec_.size())
        {
            return -1;
        }

        m_dist_.param(decltype(m_dist_)::param_type{ m_current_, m_vec_.size() - 1ULL });

        std::swap<>(m_vec_[m_current_], m_vec_[m_dist_(m_rng_)]);

        const auto val = m_vec_[m_current_];

        ++m_current_;

        return static_cast<std::ptrdiff_t>(val);
    }
}
