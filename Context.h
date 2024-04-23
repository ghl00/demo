#pragma once
#include "demo.h"
#include "AudioContext.h"


struct IContext
{
    virtual ~IContext() = default;

    virtual int32_t RunOpenRCT2() = 0;
    virtual std::shared_ptr<IAudioContext> GetAudioContext() = 0;
    virtual IObjectManager& GetObjectManager() = 0;
    virtual void Dump() const = 0;
};
std::unique_ptr<IContext> CreateContext();
std::unique_ptr<IContext> CreateContext(const std::shared_ptr<IAudioContext>& audioContext);
IContext* GetContext();