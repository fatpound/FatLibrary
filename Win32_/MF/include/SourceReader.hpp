#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_macros/Win.hpp>

#include <Win32_/include/FatWin.hpp>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <wrl.h>

#include <Win32_/include/HrException.hpp>

#include <cstddef>

#include <vector>
#include <string>
#include <memory>
#include <optional>

namespace fatpound::win32::mf
{
    class SourceReader final
    {
        enum class ReadingMode
        {
            Audio = MF_SOURCE_READER_FIRST_AUDIO_STREAM,
            Video = MF_SOURCE_READER_FIRST_VIDEO_STREAM
        };
        
    public:
        explicit SourceReader(const std::wstring& filePath);

        explicit SourceReader()                        = delete;
        explicit SourceReader(const SourceReader&)     = delete;
        explicit SourceReader(SourceReader&&) noexcept = default;
        
        auto operator = (const SourceReader&)     -> SourceReader& = delete;
        auto operator = (SourceReader&&) noexcept -> SourceReader& = default;
        ~SourceReader() noexcept                                   = default;


    public:
        [[nodiscard]]
        auto GetWaveformatOfAudioFile() -> WAVEFORMATEX;

        void ReadAudioPCM(std::vector<std::byte>& outPcmData, const std::optional<WAVEFORMATEX> targetFormat); // assumes pcmData is empty


    protected:


    private:
        void SelectStream_(const ReadingMode mode);
        void SetOutputFormatToPCM_(const std::optional<WAVEFORMATEX> targetFormat);


    private:
        Microsoft::WRL::ComPtr<IMFSourceReader> m_pReader_;
    };
}

#endif
