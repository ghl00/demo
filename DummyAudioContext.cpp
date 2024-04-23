#include "AudioContext.h"

class DummyAudioContext final : public IAudioContext
{

};

std::unique_ptr<IAudioContext> CreateDummyAudioContext()
{
    return std::make_unique<DummyAudioContext>();
}