#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include "Libav.h"

class AudioDevice
{
    public: AudioDevice();
    public: virtual ~AudioDevice();

    public: virtual bool Init(unsigned int SampleRate, unsigned int ChannelCount, SampleFormat Format) = 0;
    public: virtual void Release() = 0;
    public: virtual void Play(unsigned char* Data, size_t SampleCount) = 0;
};

#endif // AUDIODEVICE_H
