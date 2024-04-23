#pragma once
#include "demo.h"

struct IAudioContext
{
    virtual ~IAudioContext() = default;


};

std::unique_ptr<IAudioContext> CreateDummyAudioContext();
