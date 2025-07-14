#pragma once

#include <Traits/Extents.hpp>

#include <cstdlib>

#if defined(_MSVC_STL_VERSION) or defined(FATLIB_BUILDING_ON_WINDOWS)
    #define FATLIB_MEMORY_ALIGNED_ALLOCATOR _aligned_malloc
    #define FATLIB_MEMORY_ALIGNED_FREER     _aligned_free
#else
    #define FATLIB_MEMORY_ALIGNED_ALLOCATOR std::aligned_alloc
    #define FATLIB_MEMORY_ALIGNED_FREER     std::free
#endif

#include <cstddef>

#include <type_traits>
#include <memory>
#include <stdexcept>

namespace fatpound::memory::details
{
    template <typename T>
    struct AlignedUPtr
    {
        using ptr_type = std::unique_ptr<T, decltype(&FATLIB_MEMORY_ALIGNED_FREER)>;
    };

    template <typename T>
    struct AlignedUPtr<T[]>
    {
        using ptr_type = std::unique_ptr<T[], decltype(&FATLIB_MEMORY_ALIGNED_FREER)>;
    };
}

namespace fatpound::memory
{
    template <typename T>
    using AlignedUniquePtr = details::AlignedUPtr<T>::ptr_type;

    template <typename T>
    static auto AlignedAlloc(const std::size_t& alignBytes, const std::size_t& size) -> T*
    {
        if (auto* const ptr = static_cast<T*>(
#if defined(_MSVC_STL_VERSION) or defined(FATLIB_BUILDING_ON_WINDOWS)
            FATLIB_MEMORY_ALIGNED_ALLOCATOR(size * sizeof(T), alignBytes)
#else
            FATLIB_MEMORY_ALIGNED_ALLOCATOR(alignBytes, size * sizeof(T))
#endif
            ))
        {
            return ptr;
        }

        throw std::runtime_error{ "Aligned allocation failed!" };
    }

    template <traits::Array T>
    static auto MakeAlignedUniquePtr(const std::size_t& alignBytes, const std::size_t& size)
    {
        return AlignedUniquePtr<T>(AlignedAlloc<std::remove_all_extents_t<T>>(alignBytes, size), &FATLIB_MEMORY_ALIGNED_FREER);
    }

    template <typename T>
    static auto MakeAlignedUniquePtr(const std::size_t& alignBytes)
    {
        return AlignedUniquePtr<T>(AlignedAlloc<T>(alignBytes, 1U), &FATLIB_MEMORY_ALIGNED_FREER);
    }

    void AlignedFree(void* ptr) noexcept;
}
