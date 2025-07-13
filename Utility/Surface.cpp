#include <Utility/Surface.hpp>

#include <gdiplus.h>

#include <Utility/Common.hpp>

#include <cstring>

namespace fatpound::utility
{
#ifdef FATLIB_BUILDING_WITH_MSVC

    Surface::Surface(const std::filesystem::path& path,         const Size_t& alignBytes)
        :
        Surface(path.wstring(), alignBytes)
    {

    }
    Surface::Surface(const std::string&       filename,         const Size_t& alignBytes)
        :
        Surface(To_WString(filename), alignBytes)
    {

    }
    Surface::Surface(const std::wstring&      filename,         const Size_t& alignBytes)
        :
        m_pBuffer_(nullptr, nullptr)
    {
        FATSPACE_WIN32::gdi_plus::Manager gdiplusmgr;

        Gdiplus::Bitmap bitmap(filename.c_str());

        if (bitmap.GetLastStatus() not_eq Gdiplus::Ok)
        {
            throw std::runtime_error("GDI+ Bitmap error in Surface ctor!");
        }

        const auto& width = bitmap.GetWidth();
        const auto& height = bitmap.GetHeight();

        Surface surf(width, height, alignBytes);

        for (auto y = 0U; y < height; ++y)
        {
            for (auto x = 0U; x < width; ++x)
            {
                Gdiplus::Color c;

                bitmap.GetPixel(static_cast<INT>(x), static_cast<INT>(y), &c);
                surf.PutPixel<>(x, y, Color{ c.GetValue() });
            }
        }

        *this = std::move(surf);
    }

#endif

    Surface::Surface(const gfx::SizePack& dimensions,           const Size_t& alignBytes)
        :
        m_pBuffer_(memory::MakeAlignedUniquePtr<ColorArr_t>(alignBytes, static_cast<std::size_t>(dimensions.m_width* dimensions.m_height))),
        m_size_pack_(dimensions),
        m_align_byte_(alignBytes),
        m_pixel_pitch_(CalculatePixelPitch(GetWidth<>(), GetAlignment<>()))
    {

    }
    Surface::Surface(const Size_t& width, const Size_t& height, const Size_t& alignBytes)
        :
        Surface(gfx::SizePack{ .m_width = width, .m_height = height }, alignBytes)
    {

    }

    Surface::Surface() noexcept
        :
        m_pBuffer_(nullptr, nullptr)
    {

    }
    Surface::Surface(const Surface& src)
        :
        Surface(src.GetSizePack(), src.GetAlignment<>())
    {
        DeepCopyFrom_(src);
    }
    Surface::Surface(Surface&& src) noexcept
        :
        m_pBuffer_(std::move<>(src.m_pBuffer_)),
        m_size_pack_(src.GetWidth<>(), src.GetHeight<>()),
        m_align_byte_(src.GetAlignment<>()),
        m_pixel_pitch_(src.GetPixelPitch<>())
    {
        src.Reset();
    }

    auto Surface::operator = (const Surface& src) -> Surface&
    {
        if (this not_eq std::addressof(src))
        {
            Reset();

            m_pBuffer_ = memory::MakeAlignedUniquePtr<ColorArr_t>(src.GetAlignment(), static_cast<std::size_t>(src.GetWidth<>() * src.GetHeight<>()));

            m_size_pack_ = src.GetSizePack();
            m_align_byte_ = src.GetAlignment<>();
            m_pixel_pitch_ = src.GetPixelPitch<>();

            DeepCopyFrom_(src);
        }

        return *this;
    }
    auto Surface::operator = (Surface&& src) noexcept -> Surface&
    {
        if (this not_eq std::addressof<>(src))
        {
            Reset();

            m_pBuffer_ = std::move<>(src.m_pBuffer_);

            m_size_pack_ = src.GetSizePack();
            m_align_byte_ = src.GetAlignment<>();
            m_pixel_pitch_ = src.GetPixelPitch<>();

            src.Reset();
        }

        return *this;
    }


    Surface::operator const Color* () const & noexcept
    {
        return m_pBuffer_.get();
    }
    Surface::operator       Color* () & noexcept
    {
        return m_pBuffer_.get();
    }
    Surface::operator         bool () const noexcept
    {
        return IsEmpty();
    }

    auto Surface::CalculatePixelPitch(const Size_t& width, const Size_t& alignBytes) noexcept -> Size_t
    {
        assert(alignBytes % 4 == 0);
        assert(alignBytes >= sizeof(Color));
        assert(alignBytes <= width);

        const auto& pixelsPerAlign = alignBytes / static_cast<Size_t>(sizeof(Color));
        const auto& overrunCount = width % pixelsPerAlign;

        return width + ((pixelsPerAlign - overrunCount) % pixelsPerAlign);
    }

    auto Surface::ReleaseAndReset() noexcept -> Color*
    {
        auto* const ptr = m_pBuffer_.release();

        Reset();

        return ptr;
    }

    auto Surface::GetSizePack () const noexcept -> gfx::SizePack
    {
        return m_size_pack_;
    }
    auto Surface::IsEmpty     () const noexcept -> bool
    {
        return m_pBuffer_ == nullptr;
    }
    auto Surface::IsNotEmpty  () const noexcept -> bool
    {
        return not IsEmpty();
    }

    void Surface::Fill(const Color& color) noexcept
    {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
        std::memset(
            *this,
            static_cast<int>(color),
            GetWidth<std::size_t>() * GetHeight<std::size_t>() * sizeof(Color)
        );
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    }
    void Surface::Reset() noexcept
    {
        if (m_pBuffer_ not_eq nullptr)
        {
            m_pBuffer_.reset();
        }

        m_size_pack_.m_width = static_cast<Size_t>(0);
        m_size_pack_.m_height = static_cast<Size_t>(0);
        m_align_byte_ = static_cast<Size_t>(0);
        m_pixel_pitch_ = static_cast<Size_t>(0);
    }

    void Surface::DeepCopyFrom_(const Surface& src) noexcept
    {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
        Color* const pDest = *this;
        const Color* const pSrc = src;

        const auto srcPitch = src.GetPitch<>();

        for (auto y = 0U; y < src.GetHeight<>(); ++y)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            std::memcpy(
                &pDest[y * GetPixelPitch<std::size_t>()],
                &pSrc[y * src.GetPixelPitch<std::size_t>()],
                srcPitch
            );
            // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    }
}
