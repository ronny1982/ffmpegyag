#include "AudioDevice.h"

#ifdef __LINUX__
#include "AlsaDevice.h"
#endif
#ifdef __WINDOWS__
#include "WinMMDevice.h"
#endif

AudioDevice::AudioDevice()
{
    //
}

AudioDevice::~AudioDevice()
{
    //
}

AudioDevice* AudioDevice::Create()
{
    #ifdef __LINUX__
    return (AudioDevice*)(new AlsaDevice());
    #endif
    #ifdef __WINDOWS__
    return (AudioDevice*)(new WinMMDevice());
    #endif
}
