#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include "Libav.h"

enum AudioAPI
{
    AlsaAPI,
    // MMediaAPI,
};

class AudioDevice
{
    public: AudioDevice();
    public: virtual ~AudioDevice();

    // static functions (instance creation)
    public: static AudioDevice* Create(AudioAPI DeviceType);

    // interface functions
    public: virtual bool Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat SampleFormat) = 0;
    public: virtual void Release() = 0;
    public: virtual void Play(unsigned char* Data, size_t SampleCount) = 0;
};

#endif // AUDIODEVICE_H
