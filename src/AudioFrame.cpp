#include "AudioFrame.h"

AudioFrame::AudioFrame()
{
    Timestamp = int64_t(0);
    Timecode = int64_t(0);
    Duration = int64_t(0);
    SampleRate = 0;
    ChannelCount = 0;
    AlsaFormat = SND_PCM_FORMAT_S16_LE;
    SampleCount = 0;
    DataSize = av_samples_get_buffer_size(NULL, ChannelCount, SampleCount, AV_SAMPLE_FMT_S16, 1);
    Data = (unsigned char*)av_malloc(DataSize);
    FrameSize = DataSize / SampleCount;
    SampleSize = FrameSize / ChannelCount;
    // silence
    for(size_t i=0; i<DataSize; i++)
    {
        Data[i] = (unsigned char)0;
    }
}

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, SampleFormat FrameFormat, size_t FrameSampleCount)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    ChannelCount = FrameChannels;
    AlsaFormat = Libav::GetAlsaFormat(FrameFormat);
    SampleCount = FrameSampleCount;
    DataSize = av_samples_get_buffer_size(NULL, FrameChannels, FrameSampleCount, FrameFormat, 1);
    FrameSize = DataSize / SampleCount;
    SampleSize = FrameSize / ChannelCount;
    Data = (unsigned char*)av_malloc(DataSize);
}

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, size_t FrameSampleCount, int Frequency)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    ChannelCount = FrameChannels;
    AlsaFormat = SND_PCM_FORMAT_S16_LE;
    SampleCount = FrameSampleCount;
    DataSize = av_samples_get_buffer_size(NULL, FrameChannels, FrameSampleCount, AV_SAMPLE_FMT_S16, 1);
    FrameSize = DataSize / SampleCount;
    SampleSize = FrameSize / ChannelCount;
    Data = (unsigned char*)av_malloc(DataSize);

    int amp = 6000/SampleCount;
    short* tmp = (short*)Data;
    for(int i=0; i<SampleCount; i+=ChannelCount)
    {
        for(int c=0; c<ChannelCount; ++c)
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
