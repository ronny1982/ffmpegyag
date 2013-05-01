#include "AudioDevice.h"

AudioDevice::AudioDevice()
{
    //
}

AudioDevice::~AudioDevice()
{
    //
}

AudioDevice* AudioDevice::Create(AudioAPI DviceType)
{
    AudioDevice* Device = NULL;
    if(DeviceType == AlsaAPI)
    {
        // load alsa shared library
        // find function CreateAudioDevice() in shared lib
        Device = CreateAudioDevice();
    }
    return Device;
}
