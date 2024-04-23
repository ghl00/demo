#include "Context.h"
#include "AudioContext.h"
#include "Audio.h"
#include "ObjectManager.h"
#include "ObjectRepository.h"

class Context final : public IContext
{
private:
    std::shared_ptr<IAudioContext> const _audioContext;
    bool _initialised = false;

    std::unique_ptr<IObjectRepository> _objectRepository;
    std::unique_ptr<IObjectManager> _objectManager;

public:
    static Context* Instance;

public:
    Context(const std::shared_ptr<IAudioContext>& audioContext)
        : _audioContext(audioContext)
    {
        // Can't have more than one context currently.
        assert(Instance == nullptr);
        Instance = this;
    }

    ~Context()
    {
        Instance = nullptr;
    }


    std::shared_ptr<IAudioContext> GetAudioContext() override
    {
        return _audioContext;
    }

    IObjectManager& GetObjectManager() override
    {
        return *_objectManager;
    }


    int32_t RunOpenRCT2() override
    {
        if (Initialise())
        {
            //Launch();
            return 0;
        }
        return -1;
    }

    bool Initialise()
    {
        if (_initialised)
        {
            throw std::runtime_error("Context already initialised.");
        }
        _initialised = true;

        _objectRepository = CreateObjectRepository();
        _objectManager = CreateObjectManager(*_objectRepository);

        {
            Audio::Init();
            Dump();
            Audio::PopulateDevices();
            Dump();
            //InitRideSoundsAndInfo();
            //gGameSoundsOff = !gConfigSound.master_sound_enabled;
        }

        return true;
    }

    void Dump() const override
    {
        std::cout << "_audioContext: " << _audioContext << ", use_count: " << _audioContext.use_count() << "\n";
    }
};
Context* Context::Instance = nullptr;

std::unique_ptr<IContext> CreateContext()
{
    return CreateContext(CreateDummyAudioContext());
}

std::unique_ptr<IContext> CreateContext(const std::shared_ptr<IAudioContext>& audioContext)
{
    return std::make_unique<Context>(audioContext);
}

IContext* GetContext()
{
    return Context::Instance;
}
