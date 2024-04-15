#include "AudioMixer.h"


SDLAudioSource::~SDLAudioSource()
{
    std::cout << "SDLAudioSource dtor!\n";
}

bool SDLAudioSource::IsReleased() const
{
    return _released;
}

ISDLAudioChannel* AudioChannel::Create(int loop)
{
    return new AudioChannelImpl(loop);
}

ISDLAudioChannel::~ISDLAudioChannel()
{
    std::cout << "ISDLAudioChannel dtor!\n";
}

void AudioMixer::Play()
{
    for (int i = 1; i < 4; i++)
    {
        _channels.push_back(std::make_shared<AudioChannelImpl<SDLAudioSource>>(i));
    }
}

AudioMixer::~AudioMixer()
{
    _channels.clear();
}

void AudioMixer::GetNextAudioChunk()
{
    auto it = _channels.begin();
    while (it != _channels.end())
    {
        auto& channel = *it;
        if (channel->GetLoop() == 3)
        {
            it = _channels.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

ISDLAudioChannel* AudioMixer::GetChannel()
{
    auto it = _channels.begin();
    while (it != _channels.end())
    {
        auto& channel = *it;
        if (channel->GetLoop() == 2)
        {
            return channel.get();
        }
        else
        {
            ++it;
        }
    }
    return nullptr;
}

SDLAudioSource* AudioMixer::AddSource(std::unique_ptr<SDLAudioSource> source)
{
    if (source != nullptr)
    {
        _sources.push_back(std::move(source));
        return _sources.back().get();
    }
    return nullptr;
}

void AudioMixer::RemoveReleasedSources()
{
    _sources.erase(
        std::remove_if(
            _sources.begin(), _sources.end(),
            [](std::unique_ptr<SDLAudioSource>& source) {
                {
                    return source->IsReleased();
                }
            }),
        _sources.end());
}

void AudioMixer::Dump()
{
    for (auto it : _channels)
    {
        std::cout << "loop: " << it->GetLoop() << "\n";
    }
    
    auto source = _sources.begin();
    while (source != _sources.end())
    {
        std::cout << "dataLength: " << (*source)->GetDataLength() << "\n";
        ++source;
    }
}

void AudioMixer::DumpChannelUserCount()
{
    for (auto& it : _channels)
    {
        std::cout << "_channels.use_count(): " << it.use_count() << "\n";
    }
}

void AudioMixer::DumpChannelUserCount(std::shared_ptr<ISDLAudioChannel>& channel)
{
    std::cout << "channel.use_count(): " << channel.use_count() << "\n";
}

std::unique_ptr<SDLAudioSource> CreateAudioSource(uint64_t dataLength)
{
    return std::make_unique<FlacAudioSource>(dataLength);
}

void DemoAudioMixer()
{
    std::unique_ptr<AudioMixer> _audioMixer;
    _audioMixer = std::make_unique<AudioMixer>();
    _audioMixer->Play();
    _audioMixer->GetNextAudioChunk();
    _audioMixer->DumpChannelUserCount();

    for (int i = 1; i < 5; i++)
    {
        auto source = CreateAudioSource(1024 * i);
        _audioMixer->AddSource(std::move(source));
    }
    _audioMixer->Dump();
}



