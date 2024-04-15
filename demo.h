#pragma once

class SDLAudioSource
{
private:
    bool _released{};
public:
    virtual ~SDLAudioSource();
    bool IsReleased() const;
    virtual uint64_t GetDataLength() const = 0;
};

class FlacAudioSource final : public SDLAudioSource
{
private:
    uint64_t _dataLength;
public:
    FlacAudioSource(uint64_t dataLength) : _dataLength(dataLength) {};
    uint64_t GetDataLength() const override
    {
        return _dataLength;
    }
};



struct ISDLAudioChannel
{
    virtual ~ISDLAudioChannel();

    virtual int GetLoop() const = 0;
    virtual void SetLoop(int loop) = 0;
};

template<typename AudioSource_ = SDLAudioSource>
class AudioChannelImpl final : public ISDLAudioChannel
{
private:
    int _loop;

public:
    virtual ~AudioChannelImpl() = default;
    AudioChannelImpl(int loop) : _loop(loop) {};

    int GetLoop() const override
    {
        return _loop;
    }

    void SetLoop(int loop) override
    {
        _loop = loop;
    }
};

class AudioMixer
{
private:
    std::vector<std::unique_ptr<SDLAudioSource>> _sources;
    std::list<std::shared_ptr<ISDLAudioChannel>> _channels;

public:
    virtual ~AudioMixer();
    void Play();
    void GetNextAudioChunk();
    ISDLAudioChannel* GetChannel();
    SDLAudioSource* AddSource(std::unique_ptr<SDLAudioSource> source);
    void RemoveReleasedSources();
    void Dump();
    void DumpChannelUserCount();
    void DumpChannelUserCount(std::shared_ptr<ISDLAudioChannel>& channel);

};

namespace AudioChannel
{
    ISDLAudioChannel* Create(int loop);
}