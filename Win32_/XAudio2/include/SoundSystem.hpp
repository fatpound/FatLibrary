#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>
#include <xaudio2.h>
#include <wrl.h>

#include <_macros/Win.hpp>

#include <Win32_/include/HrException.hpp>
#include <Win32_/MF/include/SourceReader.hpp>

#include <cassert>
#include <cstddef>

#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <span>

namespace fatpound::win32::xaudio2
{
    class SoundSystem final
    {
        class Channel_;

    public:
        class Sound final
        {
            friend Channel_;

        public:
            explicit Sound(const std::wstring& filePath, const WAVEFORMATEX& format);

            explicit Sound()                 = delete;
            explicit Sound(const Sound&)     = delete;
            explicit Sound(Sound&&) noexcept = delete;

            auto operator = (const Sound&)     -> Sound& = delete;
            auto operator = (Sound&&) noexcept -> Sound& = delete;
            ~Sound();


        public:
            auto GetData   () const noexcept -> std::span<const std::byte>;
            auto GetFormat () const noexcept -> WAVEFORMATEX;

            void Play(SoundSystem& sys, const float volume = 1.0F, const float freqMod = 1.0F);


        protected:


        private:
            void AddChannel_    (Channel_& channel);
            void RemoveChannel_ (Channel_& channel);


        private:
            std::vector<std::byte>   m_pcm_data_{};
            WAVEFORMATEX             m_format_{};
            std::vector<Channel_*>   m_active_channel_ptrs_;

            std::mutex               m_mtx_;
        };


    public:
        explicit SoundSystem(const WAVEFORMATEX& masterFormat = S_DefaultFormat_());
        explicit SoundSystem(const SoundSystem&)     = delete;
        explicit SoundSystem(SoundSystem&&) noexcept = delete;

        auto operator = (const SoundSystem&)     -> SoundSystem& = delete;
        auto operator = (SoundSystem&&) noexcept -> SoundSystem& = delete;
        ~SoundSystem() noexcept;


    public:
        auto GetMasterFormat() const noexcept -> WAVEFORMATEX;
        
        void PlaySound(Sound& sound, const float volume, const float freqMod);
        void SetMasterVolume(const float volume) noexcept;


    protected:


    private:
        class VoiceCallback_ final : public IXAudio2VoiceCallback
        {
        public:
            explicit VoiceCallback_(SoundSystem& sys) noexcept;

            explicit VoiceCallback_()                          = delete;
            explicit VoiceCallback_(const VoiceCallback_&)     = delete;
            explicit VoiceCallback_(VoiceCallback_&&) noexcept = delete;

            auto operator = (const VoiceCallback_&)     -> VoiceCallback_& = delete;
            auto operator = (VoiceCallback_&&) noexcept -> VoiceCallback_& = delete;
            virtual ~VoiceCallback_() noexcept                             = default;

        public:
            virtual void STDMETHODCALLTYPE OnVoiceProcessingPassStart (UINT32 BytesRequired)                noexcept override final;
            virtual void STDMETHODCALLTYPE OnVoiceProcessingPassEnd   ()                                    noexcept override final;
            virtual void STDMETHODCALLTYPE OnStreamEnd                ()                                    noexcept override final;
            virtual void STDMETHODCALLTYPE OnBufferStart              (void* pBufferContext)                noexcept override final;
            virtual void STDMETHODCALLTYPE OnBufferEnd                (void* pBufferContext)                         override final;
            virtual void STDMETHODCALLTYPE OnLoopEnd                  (void* pBufferContext)                noexcept override final;
            virtual void STDMETHODCALLTYPE OnVoiceError               (void* pBufferContext, HRESULT Error) noexcept override final;

        protected:

        private:
            SoundSystem& m_sys_;
        };
        class Channel_       final
        {
            friend VoiceCallback_;

        public:
            explicit Channel_(SoundSystem& sys);

            explicit Channel_()                    = delete;
            explicit Channel_(const Channel_&)     = default;
            explicit Channel_(Channel_&&) noexcept = default;

            auto operator = (const Channel_&)     -> Channel_& = default;
            auto operator = (Channel_&&) noexcept -> Channel_& = default;
            ~Channel_() noexcept;

        public:
            void Play(Sound& sound, const float volume, const float freqMod);
            void Stop() noexcept;

        protected:

        private:
            void RemoveFromSoundList();

        private:
            XAUDIO2_BUFFER         m_xabuf_{};
            IXAudio2SourceVoice*   m_pSourceVoice_{};
            Sound*                 m_pSound_{};
        };


    private:
        static constexpr auto S_DefaultFormat_() noexcept -> WAVEFORMATEX
        {
            return
            {
                .wFormatTag      = WAVE_FORMAT_PCM,
                .nChannels       = 2,
                .nSamplesPerSec  = 44100,
                .nAvgBytesPerSec = 44100 * 2 * 24 / 8,
                .nBlockAlign     = static_cast<WORD>(2 * 24 / 8),
                .wBitsPerSample  = 24,
                .cbSize          = 0U
            };
        }


    private:
        void DeactivateChannel_(Channel_& channel);


    private:
        static constexpr auto                    scx_channel_count_{ 64ULL };

        Microsoft::WRL::ComPtr<IXAudio2>         m_pXAudio2_;
        IXAudio2MasteringVoice*                  m_pMasterVoice_{};
        WAVEFORMATEX                             m_master_voice_format_;

        std::vector<std::unique_ptr<Channel_>>   m_idle_channel_ptrs_;
        std::vector<std::unique_ptr<Channel_>>   m_active_channel_ptrs_;

        std::mutex                               m_mtx_;

        VoiceCallback_                           m_voice_callback_;
    };

    using Sound = SoundSystem::Sound;
}

#endif
