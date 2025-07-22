#include "../include/Common.hpp"

namespace fatpound::memory
{
    void AlignedFree(void* const ptr) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-no-malloc, hicpp-no-malloc)
        FATLIB_MEMORY_ALIGNED_FREER(ptr);
        // NOLINTEND(cppcoreguidelines-no-malloc, hicpp-no-malloc)
    }
}
