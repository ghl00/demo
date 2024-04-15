#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <chrono>
#include <utility>
#include <algorithm>
#include <sstream>
#include <new>
#include <memory>
#include "demo.h"
#include "AudioMixer.h"

int main()
{
    std::unique_ptr<AudioMixer> _audioMixer;
    _audioMixer = std::make_unique<AudioMixer>();
    _audioMixer->Play();
    _audioMixer->GetNextAudioChunk();
    _audioMixer->DumpChannelUserCount();

    for (int i = 1; i < 5; i++)
    {
        auto source = CreateAudioSource(1024*i);
        _audioMixer->AddSource(std::move(source));
    }
    _audioMixer->Dump();

    return 0;
}



