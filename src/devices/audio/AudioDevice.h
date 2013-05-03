#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include "../../Libav.h"

class AudioDevice
{
    public: AudioDevice();
    public: virtual ~AudioDevice();

    // static function (instance creation)
    public: static AudioDevice* Create();

    // interface functions
    public: virtual bool Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat SampleFormat) = 0;
    public: virtual void Release() = 0;
    public: virtual void Play(unsigned char* Data, size_t SampleCount) = 0;
};

#endif // AUDIODEVICE_H
