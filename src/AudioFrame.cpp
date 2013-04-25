#include "AudioFrame.h"

AudioFrame::AudioFrame()
{
    Timestamp = int64_t(0);
    Timecode = int64_t(0);
    Duration = int64_t(0);
    SampleRate = 0;
    Channels = 0;
    AVFormat = AV_SAMPLE_FMT_S16;
    DataSize = 2*Channels*SampleRate*Duration/1000; // format*channels*samplerate*duration/[milliseconds]
    Data = (unsigned char*)av_malloc(DataSize);
    // silence
    for(size_t i=0; i<DataSize; i++)
    {
        Data[i] = (unsigned char)0;
    }
}

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, SampleFormat FrameFormat, size_t FrameDataSize, unsigned char* FrameData)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    Channels = FrameChannels;
    AVFormat = FrameFormat;
    DataSize = FrameDataSize;
    Data = FrameData;
}

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, int Frequency)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    Channels = FrameChannels;
    AVFormat = AV_SAMPLE_FMT_S16;
    DataSize = 2*Channels*SampleRate*Duration/1000; // format*channels*samplerate*duration/[milliseconds]
    Data = (unsigned char*)av_malloc(DataSize);

    int range = SampleRate/Frequency;
    int amp = 8000/range;
    short* tmp = (short*)Data;
    for(int i=0; i<Channels*SampleRate*Duration/1000; i+=Channels)
    {
        for(int c=0; c<Channels; c+=2)
        {
            tmp[i+c] = amp*(i%range);
        }
    }
    tmp = NULL;
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
