#ifndef ALSADEVICE_H
#define ALSADEVICE_H

#include "AudioDevice.h"
#include <alsa/asoundlib.h>

class AlsaDevice : public AudioDevice
{
    public: AlsaDevice();
    public: virtual ~AlsaDevice();

    public: bool Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat SampleFormat);
    public: void Release();
    public: void Play(unsigned char* FrameData, size_t SampleCount);
    private: snd_pcm_format_t GetAlsaFormat(AVSampleFormat Format);

    private: snd_pcm_t* Device;
};

AlsaDevice* CreateAudioDevice();

#endif // ALSADEVICE_H
