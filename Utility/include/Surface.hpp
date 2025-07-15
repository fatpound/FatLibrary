#pragma once

#include <_macros/Compiler.hpp>
#include <_macros/Namespaces.hpp>

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <Win32_/GDI_Plus/include/Manager.hpp>
#endif

#include <Memory/Memory.hpp>

#include <Traits/include/Bitwise.hpp>
#include <Utility/include/Color.hpp>
#include <Utility/Gfx/include/SizePack.hpp>

#include <cassert>
#include <cstdint>

#include <string>
#include <type_traits>
#include <filesystem>
#include <concepts>

namespace fatpound::utility
{
    /// @brief Represents a 2D pixel surface with aligned memory storage, supporting pixel access, modification
    ///
    class Surface final
    {
        using Color_t    = Color;
        using ColorArr_t = Color_t[];
        using Ptr_t      = memory::AlignedUniquePtr<ColorArr_t>;

    public:
        using Size_t = std::uint32_t;


    public:
        static constexpr Size_t scx_DefaultAlignment = 16U;


    public:
#ifdef FATLIB_BUILDING_WITH_MSVC
        explicit Surface(const std::filesystem::path& path,         const Size_t& alignBytes = scx_DefaultAlignment);
        explicit Surface(const std::string&       filename,         const Size_t& alignBytes = scx_DefaultAlignment);
        explicit Surface(const std::wstring&      filename,         const Size_t& alignBytes = scx_DefaultAlignment);
#endif
        explicit Surface(const gfx::SizePack& dimensions,           const Size_t& alignBytes = scx_DefaultAlignment);
        explicit Surface(const Size_t& width, const Size_t& height, const Size_t& alignBytes = scx_DefaultAlignment);

        explicit Surface() noexcept;
        Surface(const Surface& src);
        Surface(Surface&& src) noexcept;

        auto operator = (const Surface& src)     -> Surface&;
        auto operator = (Surface&& src) noexcept -> Surface&;
        ~Surface() noexcept = default;


    public:
        // NOLINTBEGIN(google-explicit-constructor, hicpp-explicit-conversions)
        operator const Color* () const & noexcept;
        operator       Color* ()       & noexcept;
        // NOLINTEND(google-explicit-constructor, hicpp-explicit-conversions)

        explicit operator bool () const noexcept;

        
    public:
        static auto CalculatePixelPitch(const Size_t& width, const Size_t& alignBytes) noexcept -> Size_t;


    public:
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetWidth      () const noexcept -> T
        {
            return static_cast<T>(m_size_pack_.m_width);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetHeight     () const noexcept -> T
        {
            return static_cast<T>(m_size_pack_.m_height);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetAlignment  () const noexcept -> T
        {
            return static_cast<T>(m_align_byte_);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetPixelPitch () const noexcept -> T
        {
            return static_cast<T>(m_pixel_pitch_);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetPitch      () const noexcept -> T
        {
            return static_cast<T>(m_pixel_pitch_ * sizeof(Color));
        }

        template <std::unsigned_integral T> [[nodiscard]] FATLIB_FORCEINLINE auto GetPixel(const T& x, const T& y) const -> Color
        {
            assert(x < GetWidth<T>());
            assert(y < GetHeight<T>());

            return m_pBuffer_[(y * m_pixel_pitch_) + x];
        }
        template <std::signed_integral T>   [[nodiscard]] FATLIB_FORCEINLINE auto GetPixel(const T& x, const T& y) const -> Color
        {
            assert(x >= 0);
            assert(y >= 0);

            return GetPixel<>(
                static_cast<std::make_unsigned_t<T>>(x),
                static_cast<std::make_unsigned_t<T>>(y)
            );
        }
        template <std::unsigned_integral T>               FATLIB_FORCEINLINE void PutPixel(const T& x, const T& y, const Color& color) noexcept
        {
            assert(x < GetWidth<T>());
            assert(y < GetHeight<T>());

            m_pBuffer_[(y * m_pixel_pitch_) + x] = color;
        }
        template <std::signed_integral T>                 FATLIB_FORCEINLINE void PutPixel(const T& x, const T& y, const Color& color) noexcept
        {
            assert(x >= 0);
            assert(y >= 0);

            PutPixel<>(
                static_cast<std::make_unsigned_t<T>>(x),
                static_cast<std::make_unsigned_t<T>>(y),
                color
            );
        }


    public:
        auto ReleaseAndReset() noexcept -> Color*;

        [[nodiscard]] auto GetSizePack () const noexcept -> gfx::SizePack;
        [[nodiscard]] auto IsEmpty     () const noexcept -> bool;
        [[nodiscard]] auto IsNotEmpty  () const noexcept -> bool;

        void Fill(const Color& color) noexcept;
        void Reset() noexcept;


    protected:


    private:
        void DeepCopyFrom_(const Surface& src) noexcept;


    private:
        Ptr_t           m_pBuffer_;

        gfx::SizePack   m_size_pack_;

        Size_t          m_align_byte_{};
        Size_t          m_pixel_pitch_{};
    };
}
