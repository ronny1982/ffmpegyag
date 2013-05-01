#include "AlsaDevice.h"

AlsaDevice::AlsaDevice()
{
    //
}

AlsaDevice::~AlsaDevice()
{
    Release();
}

bool AlsaDevice::Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat SampleFormat)
{
    if(snd_pcm_open(&Device, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
    {
        return false;
    }

    snd_pcm_hw_params_t* HardwareParameters;
    snd_pcm_hw_params_malloc(&HardwareParameters);
    snd_pcm_hw_params_any(Device, HardwareParameters);
    snd_pcm_hw_params_set_access(Device, HardwareParameters, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_channels(Device, HardwareParameters, ChannelCount);
    snd_pcm_hw_params_set_format(Device, HardwareParameters, GetAlsaFormat(SampleFormat));
    snd_pcm_hw_params_set_rate(Device, HardwareParameters, SampleRate, 0);
    snd_pcm_hw_params(Device, HardwareParameters);
    snd_pcm_hw_params_free(HardwareParameters);
    snd_pcm_prepare(Device);
    return true;
}

void AlsaDevice::Release()
{
    //snd_pcm_drain(Device); // stopping after all remaining frames in the buffer have finished playing
    snd_pcm_drop(Device); // immediately stops playback, dropping any frames still left in the buffer
    snd_pcm_close(Device);
    Device = NULL;
}

void AlsaDevice::Play(unsigned char* Data, size_t SampleCount)
{
    snd_pcm_writei(Device, Data, SampleCount);
}

snd_pcm_format_t AlsaDevice::GetAlsaFormat(AVSampleFormat Format)
{
    // NOTE: ffmpegyag only supports interleaved formats
    switch(Format)
    {
        // interleaved formats (single array, alternating channel data)
        case AV_SAMPLE_FMT_U8:  return SND_PCM_FORMAT_U8;
        case AV_SAMPLE_FMT_S16: return SND_PCM_FORMAT_S16;
        case AV_SAMPLE_FMT_S32: return SND_PCM_FORMAT_S32;
        case AV_SAMPLE_FMT_FLT: return SND_PCM_FORMAT_FLOAT;
        case AV_SAMPLE_FMT_DBL: return SND_PCM_FORMAT_FLOAT64;
        // planar formats (multi dimensional array, one dimension for each channel)
        //case AV_SAMPLE_FMT_U8P:  return;
        //case AV_SAMPLE_FMT_S16P: return;
        //case AV_SAMPLE_FMT_S32P: return;
        //case AV_SAMPLE_FMT_FLTP: return;
        //case AV_SAMPLE_FMT_DBLP: return;
        default: return SND_PCM_FORMAT_UNKNOWN;
    }
}

AlsaDevice* CreateAudioDevice()
{
    return new AlsaDevice();
}
