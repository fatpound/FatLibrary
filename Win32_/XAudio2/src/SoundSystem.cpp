#include "SoundSystem.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#pragma comment(lib, "xaudio2")

namespace fatpound::win32::xaudio2
{
    SoundSystem::Sound::Sound(const std::wstring& filePath, const WAVEFORMATEX& format)
        :
        m_format_(format)
    {
        mf::SourceReader{ filePath }.ReadAudioPCM(m_pcm_data_, m_format_);
    }
    SoundSystem::Sound::~Sound()
    {
        {
            const std::lock_guard lg{ m_mtx_ };

            for (auto& pChan : m_active_channel_ptrs_)
            {
                pChan->Stop();
            }
        }

        bool allChannelsAreDeactivated{};

        do
        {
            const std::lock_guard lg{ m_mtx_ };

            allChannelsAreDeactivated = (m_active_channel_ptrs_.size() == 0);
        }
        while (not allChannelsAreDeactivated);
    }

    auto SoundSystem::Sound::GetData() const noexcept -> std::span<const std::byte>
    {
        return m_pcm_data_;
    }
    auto SoundSystem::Sound::GetFormat() const noexcept -> WAVEFORMATEX
    {
        return m_format_;
    }

    void SoundSystem::Sound::Play(SoundSystem& sys, const float volume, const float freqMod)
    {
        sys.PlaySound(*this, volume, freqMod);
    }

    void SoundSystem::Sound::AddChannel_(Channel_& channel)
    {
        const std::lock_guard lg{ m_mtx_ };

        m_active_channel_ptrs_.push_back(&channel);
    }
    void SoundSystem::Sound::RemoveChannel_(Channel_& channel)
    {
        const std::lock_guard lg{ m_mtx_ };

        m_active_channel_ptrs_.erase(std::ranges::find(m_active_channel_ptrs_, &channel));
    }


    SoundSystem::SoundSystem(const WAVEFORMATEX& masterFormat)
        :
        m_master_voice_format_{ masterFormat },
#ifdef _MSC_VER
#pragma region (C4355 'this' warning)
#pragma warning (push)
#pragma warning (disable : 4355)
#endif
        m_voice_callback_(*this)
#ifdef _MSC_VER
#pragma warning (pop)
#pragma endregion
#endif
    {
        FAT_THROW_HRX_IF_FAILED(XAudio2Create(&m_pXAudio2_, 0U, XAUDIO2_USE_DEFAULT_PROCESSOR), "Failed to create XAudio2 Engine!");
        FAT_THROW_HRX_IF_FAILED(m_pXAudio2_->CreateMasteringVoice(&m_pMasterVoice_), "Failed to create XAudio2 Mastering Voice!");

        for (std::size_t i{}; i < scx_channel_count_; ++i)
        {
            m_idle_channel_ptrs_.push_back(std::make_unique<Channel_>(*this));
        }
    }
    SoundSystem::~SoundSystem() noexcept
    {
        if (m_pMasterVoice_ not_eq nullptr)
        {
            m_pMasterVoice_->DestroyVoice();
            m_pMasterVoice_ = nullptr;
        }
    }


    auto SoundSystem::GetMasterFormat() const noexcept -> WAVEFORMATEX
    {
        return m_master_voice_format_;
    }

    void SoundSystem::PlaySound(Sound& sound, const float volume, const float freqMod)
    {
        const std::lock_guard lg{ m_mtx_ };

        if (m_idle_channel_ptrs_.size() > 0)
        {
            m_active_channel_ptrs_.push_back(std::move(m_idle_channel_ptrs_.back()));
            m_idle_channel_ptrs_.pop_back();
            m_active_channel_ptrs_.back()->Play(sound, volume, freqMod);
        }
    }
    void SoundSystem::SetMasterVolume(const float volume) noexcept
    {
        if (m_pMasterVoice_ not_eq nullptr)
        {
            m_pMasterVoice_->SetVolume(volume);
        }
    }

    void SoundSystem::DeactivateChannel_(Channel_& channel)
    {
        const std::lock_guard lg{ m_mtx_ };

        auto iter = std::ranges::find_if(
            m_active_channel_ptrs_,
            [&channel](const auto& pChan)
            {
                return pChan.get() == &channel;
            }
        );

        if (iter not_eq m_active_channel_ptrs_.end())
        {
            m_idle_channel_ptrs_.push_back(std::move<>(*iter));
            m_active_channel_ptrs_.erase(iter);
        }
    }


    SoundSystem::VoiceCallback_::VoiceCallback_(SoundSystem& sys) noexcept
        :
        m_sys_(sys)
    {

    }

    void SoundSystem::VoiceCallback_::OnVoiceProcessingPassStart ([[maybe_unused]] UINT32 BytesRequired) noexcept
    {

    }
    void SoundSystem::VoiceCallback_::OnVoiceProcessingPassEnd   () noexcept
    {

    }
    void SoundSystem::VoiceCallback_::OnStreamEnd                () noexcept
    {

    }
    void SoundSystem::VoiceCallback_::OnBufferStart              ([[maybe_unused]] void*       pBufferContext) noexcept
    {

    }
    void SoundSystem::VoiceCallback_::OnBufferEnd                (                 void* const pBufferContext)
    {
        auto& channel = *reinterpret_cast<Channel_*>(pBufferContext);

        channel.Stop();
        channel.RemoveFromSoundList();

        m_sys_.DeactivateChannel_(channel);
    }
    void SoundSystem::VoiceCallback_::OnLoopEnd                  ([[maybe_unused]] void*       pBufferContext) noexcept
    {

    }
    void SoundSystem::VoiceCallback_::OnVoiceError               ([[maybe_unused]] void*       pBufferContext, [[maybe_unused]] HRESULT Error) noexcept
    {

    }


    SoundSystem::Channel_::Channel_(SoundSystem& sys)
    {
        ZeroMemory(&m_xabuf_, sizeof(m_xabuf_));

        m_xabuf_.pContext = this;

        const auto& format = sys.GetMasterFormat();

        FAT_THROW_HRX_IF_FAILED(
            sys.m_pXAudio2_->CreateSourceVoice(&m_pSourceVoice_, &format, 0U, XAUDIO2_DEFAULT_FREQ_RATIO, &sys.m_voice_callback_),
            "Failed to create XAudio2 Source Voice!"
        );
    }
    SoundSystem::Channel_::~Channel_() noexcept
    {
        assert((m_pSound_ == nullptr));

        if (m_pSourceVoice_ not_eq nullptr)
        {
            m_pSourceVoice_->DestroyVoice();
            m_pSourceVoice_ = nullptr;
        }
    }

    void SoundSystem::Channel_::Play(Sound& sound, const float volume, const float freqMod)
    {
        assert(((m_pSourceVoice_ not_eq nullptr) and (m_pSound_ == nullptr)));

        sound.AddChannel_(*this);

        m_pSound_ = &sound;
        m_xabuf_.pAudioData = reinterpret_cast<const BYTE*>(sound.GetData().data());
        m_xabuf_.AudioBytes = static_cast<UINT32>(sound.GetData().size());

        m_pSourceVoice_->SubmitSourceBuffer(&m_xabuf_);
        m_pSourceVoice_->SetFrequencyRatio(freqMod);
        m_pSourceVoice_->SetVolume(volume);
        m_pSourceVoice_->Start();
    }
    void SoundSystem::Channel_::Stop() noexcept
    {
        assert((m_pSourceVoice_ not_eq nullptr)); // and (m_pSound_ not_eq nullptr)

        m_pSourceVoice_->Stop();
        m_pSourceVoice_->FlushSourceBuffers();
    }

    void SoundSystem::Channel_::RemoveFromSoundList()
    {
        m_pSound_->RemoveChannel_(*this);
        m_pSound_ = nullptr;
    }
}

#endif
