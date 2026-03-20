#pragma once

#include "IAudioEffect.hpp"

#include <cstddef>
#include <memory>

namespace fatx::gstreamer
{
    class IEffectChain
    {
    public:
        IEffectChain() noexcept                   = default;
        IEffectChain(const IEffectChain&)         = delete;
        IEffectChain(IEffectChain&&)    noexcept  = delete;

        auto operator = (const IEffectChain&)            -> IEffectChain& = delete;
        auto operator = (IEffectChain&&)       noexcept  -> IEffectChain& = delete;
        virtual ~IEffectChain() noexcept                                  = default;


    public:
        [[nodiscard]] virtual auto GetBin     () const noexcept -> GstElement* = 0;
        [[nodiscard]] virtual auto GetSinkPad () const noexcept -> GstPad*     = 0;
        [[nodiscard]] virtual auto GetSrcPad  () const noexcept -> GstPad*     = 0;
        [[nodiscard]] virtual auto Count      () const noexcept -> std::size_t = 0;

        virtual void Add(std::shared_ptr<IAudioEffect> pEffect) noexcept = 0;


    protected:


    private:
    };
}
