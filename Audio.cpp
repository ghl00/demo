#include "Audio.h"
#include "Context.h"

namespace Audio
{

    void Init()
    {
        auto audioContext = GetContext()->GetAudioContext();
        GetContext()->Dump();
    }

    void LoadAudioObjects()
    {
        auto& objManager = GetContext()->GetObjectManager();
        auto* baseAudio = objManager.LoadObject(AudioObjectIdentifiers::Rct2Base);
        if (baseAudio != nullptr)
        {
            _soundsAudioObjectEntryIndex = objManager.GetLoadedObjectEntryIndex(baseAudio);
        }
        objManager.LoadObject(AudioObjectIdentifiers::Rct2Circus);
    }
    void PopulateDevices()
    {
        auto audioContext = GetContext()->GetAudioContext();        
        GetContext()->Dump();
    }


}//namespace Audio