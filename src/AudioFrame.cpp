#include "AudioFrame.h"

AudioFrame::AudioFrame()
{
    Timestamp = int64_t(0);
    Timecode = int64_t(0);
    Duration = int64_t(0);
    SampleRate = 0;
    Channels = 0;
    AVFormat = AV_SAMPLE_FMT_S16;
    SampleCount = 0;
    DataSize = av_samples_get_buffer_size(NULL, Channels, SampleCount, AVFormat, 1);
    Data = (unsigned char*)av_malloc(DataSize);
    // silence
    for(size_t i=0; i<DataSize; i++)
    {
        Data[i] = (unsigned char)0;
    }
}

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, SampleFormat FrameFormat, int FrameSampleCount)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    Channels = FrameChannels;
    AVFormat = FrameFormat;
    SampleCount = FrameSampleCount;
    DataSize = av_samples_get_buffer_size(NULL, Channels, SampleCount, AVFormat, 1);
    Data = (unsigned char*)av_malloc(DataSize);
}

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, int FrameSampleCount, int Frequency)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    Channels = FrameChannels;
    AVFormat = AV_SAMPLE_FMT_S16;
    SampleCount = FrameSampleCount;
    DataSize = av_samples_get_buffer_size(NULL, Channels, SampleCount, AVFormat, 1);
    Data = (unsigned char*)av_malloc(DataSize);

    int amp = 6000/SampleCount;
    short* tmp = (short*)Data;
    for(int i=0; i<SampleCount; i+=Channels)
    {
        for(int c=0; c<Channels; ++c)
        {
            tmp[i+c] = amp*(i%SampleCount);
        }
    }
    tmp = NULL;
}

AudioFrame::~AudioFrame()
{
    av_free(Data);
    Data = NULL;
}

void AudioFrame::FillFrame(unsigned char* FrameData)
{
    memcpy(Data, FrameData, DataSize);
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
