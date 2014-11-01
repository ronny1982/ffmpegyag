#include "AlsaDevice.h"

#ifdef __LINUX__

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
    isPlanar = (bool)av_sample_fmt_is_planar(SampleFormat);

    snd_pcm_hw_params_t* HardwareParameters;
    snd_pcm_hw_params_malloc(&HardwareParameters);
    snd_pcm_hw_params_any(Device, HardwareParameters);
    if(isPlanar)
    {
        snd_pcm_hw_params_set_access(Device, HardwareParameters, SND_PCM_ACCESS_RW_NONINTERLEAVED);
    }
    else
    {
        snd_pcm_hw_params_set_access(Device, HardwareParameters, SND_PCM_ACCESS_RW_INTERLEAVED);
    }
    snd_pcm_hw_params_set_format(Device, HardwareParameters, GetAlsaFormat(SampleFormat));
    snd_pcm_hw_params_set_channels(Device, HardwareParameters, ChannelCount);
    snd_pcm_hw_params_set_rate(Device, HardwareParameters, SampleRate, 0);
    snd_pcm_hw_params(Device, HardwareParameters);
    snd_pcm_hw_params_free(HardwareParameters);
    snd_pcm_prepare(Device);
    return true;

    // TODO: check SND_PCM_NONBLOCK behaviour, so the parent loop can continue streaming video frames...
}

void AlsaDevice::Release()
{
    if(Device)
    {
        //snd_pcm_drain(Device); // stopping after all remaining frames in the buffer have finished playing
        snd_pcm_drop(Device); // immediately stops playback, dropping any frames still left in the buffer
        snd_pcm_close(Device);
        Device = NULL;
    }
}

void AlsaDevice::Play(unsigned char* FrameData, size_t SampleCount)
{
    // snd_pcm_status(...)
    // faster: snd_pcm_state(...)
    snd_pcm_state_t status = snd_pcm_state(Device);

    //if(status == SND_PCM_STATE_OPEN){printf("Open\n");}
    //if(status == SND_PCM_STATE_SETUP){printf("Setup installed\n");}
    //if(status == SND_PCM_STATE_PREPARED){printf("Prepared and ready to start\n");}
    //if(status == SND_PCM_STATE_RUNNING){printf("Running\n");}
    if(status == SND_PCM_STATE_XRUN)
    {
        //printf("Alsa Stopped: underrun (playback) or overrun (capture) detected\n");
        snd_pcm_prepare(Device);
    }
    //if(status == SND_PCM_STATE_DRAINING){printf("Draining: running (playback) or stopped (capture)\n");}
    //if(status == SND_PCM_STATE_PAUSED){printf("Paused\n");}
    //if(status == SND_PCM_STATE_SUSPENDED){printf("Hardware is suspended\n");}
    //if(status == SND_PCM_STATE_DISCONNECTED){printf("Hardware is disconnected\n");}

    if(isPlanar)
    {
        // FIXME: writen with two dimensional FrameData (non-interleaved)
        //snd_pcm_writen(Device, FrameData, SampleCount);
        snd_pcm_writei(Device, FrameData, SampleCount);
    }
    else
    {
        snd_pcm_writei(Device, FrameData, SampleCount);
    }

    /*
        results:
        -EBADFD     PCM is not in the right state (SND_PCM_STATE_PREPARED or SND_PCM_STATE_RUNNING)
        -EPIPE      an underrun occurred
        -ESTRPIPE   a suspend event occurred (stream is suspended and waiting for an application recovery)

    if(result < 0)
    {
        printf("ALASA: Can not write samples to device\n");
    }
    */
}

snd_pcm_format_t AlsaDevice::GetAlsaFormat(AVSampleFormat Format)
{
    printf("AVSampleFormat: %s\n", av_get_sample_fmt_name(Format));
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
        case AV_SAMPLE_FMT_U8P:  return SND_PCM_FORMAT_U8;
        case AV_SAMPLE_FMT_S16P: return SND_PCM_FORMAT_S16;
        case AV_SAMPLE_FMT_S32P: return SND_PCM_FORMAT_S32;
        case AV_SAMPLE_FMT_FLTP: return SND_PCM_FORMAT_FLOAT;
        case AV_SAMPLE_FMT_DBLP: return SND_PCM_FORMAT_FLOAT64;
        default: return SND_PCM_FORMAT_UNKNOWN;
    }
}

#endif // LINUX
