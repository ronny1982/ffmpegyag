#include "AudioFrame.h"

AudioFrame::AudioFrame()
{
    Timestamp = int64_t(0);
    Timecode = int64_t(0);
    Duration = int64_t(0);
    SampleRate = 0;
    Channels = 0;
    DataSize = 0;
    Data = (unsigned char*)av_malloc(DataSize);
    // silence
    for(size_t i=0; i<DataSize; i++)
    {
        Data[i] = (unsigned char)0;
    }
}

AudioFrame::~AudioFrame()
{
    av_free(Data);
    Data = NULL;
}

snd_pcm_format_t AudioFrame::GetPCMFormat()
{
    switch(AVFormat)
    {
        // TODO: add more formats
        case AV_SAMPLE_FMT_S16: return SND_PCM_FORMAT_S16_LE;
        default: return SND_PCM_FORMAT_UNKNOWN;
    }
}
