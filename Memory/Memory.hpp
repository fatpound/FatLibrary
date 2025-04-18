#pragma once

#if FAT_BUILDING_WITH_MSVC or FAT_BUILDING_ON_WINDOWS
#include <cstdlib>
#ifndef FAT_MEMORY_ALIGNED_ALLOCATE_WITH
    // NOLINTBEGIN(cppcoreguidelines-macro-usage)
    #define FAT_MEMORY_ALIGNED_ALLOCATE_WITH(align, size) (::_aligned_malloc(size, align))
    // NOLINTEND(cppcoreguidelines-macro-usage)
#endif
#ifndef FAT_MEMORY_ALIGNED_FREER
    #define FAT_MEMORY_ALIGNED_FREER ::_aligned_free
#endif
#else
#ifndef FAT_MEMORY_ALIGNED_ALLOCATE_WITH
    // NOLINTBEGIN(cppcoreguidelines-macro-usage)
    #define FAT_MEMORY_ALIGNED_ALLOCATE_WITH(align, size) (::std::aligned_alloc(align, size))
    // NOLINTEND(cppcoreguidelines-macro-usage)
#endif
#ifndef FAT_MEMORY_ALIGNED_FREER
    #define FAT_MEMORY_ALIGNED_FREER ::std::free
#endif
#endif

#include <cstdint>

#include <memory>
#include <stdexcept>

namespace fatpound::memory
{
    namespace details
    {
        template <typename T>
        struct AlignedUPtr
        {
            using ptr_type = ::std::unique_ptr<T,   decltype(&FAT_MEMORY_ALIGNED_FREER)>;
        };

        // NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
        template <typename T>
        struct AlignedUPtr<T[]>
        {
            using ptr_type = ::std::unique_ptr<T[], decltype(&FAT_MEMORY_ALIGNED_FREER)>;
        };
        // NOLINTEND(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
    }

    template <typename T>
    using AlignedUniquePtr = details::AlignedUPtr<T>::ptr_type;

    template <typename T>
    static auto AlignedAlloc(const ::std::size_t& alignBytes, const ::std::size_t& size) -> T*
    {
        if (auto* const ptr = static_cast<T*>(FAT_MEMORY_ALIGNED_ALLOCATE_WITH(alignBytes, (size * sizeof(T)))))
        {
            return ptr;
        }

        throw ::std::runtime_error{ "Aligned allocation failed!" };
    }

    template <typename T>
    static auto MakeAlignedUniquePtr(const ::std::size_t& alignBytes, [[maybe_unused]] const ::std::size_t& size)
    {
        if constexpr (::std::is_array_v<T>)
        {
            return AlignedUniquePtr<T>(AlignedAlloc<::std::remove_all_extents_t<T>>(alignBytes, size), &FAT_MEMORY_ALIGNED_FREER);
        }
        else
        {
            return AlignedUniquePtr<T>(AlignedAlloc<T>(alignBytes, 1U), &FAT_MEMORY_ALIGNED_FREER);
        }
    }
}
