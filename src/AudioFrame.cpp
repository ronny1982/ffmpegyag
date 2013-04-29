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
    SampleSize = DataSize / SampleCount;
    SampleFormatSize = SampleSize / ChannelCount;
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
    SampleSize = DataSize / SampleCount;
    SampleFormatSize = SampleSize / ChannelCount;
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
    SampleSize = DataSize / SampleCount;
    SampleFormatSize = SampleSize / ChannelCount;
    Data = (unsigned char*)av_malloc(DataSize);

    int amp = 6000/SampleCount;
    short* tmp = (short*)Data;
    for(size_t i=0; i<SampleCount; i+=ChannelCount)
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

// FIXME: what happens when segment FilterTime.from <= FilterTime.to ???
// should work when FilterTime.from == FilterTime.to -> pivot.from == pivot.to
void AudioFrame::FilterFrameIntersection(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, size_t* p1, size_t* p2)
{
    int64_t Endtime = Timecode + Duration;

    if(Endtime < *FilterTimeFrom)
    {
        *p1 = SampleCount;
        *p2 = SampleCount;
        return; // Outside Before
    }

    // invalid segment interval
    if(*FilterTimeFrom >= *FilterTimeTo)
    {
        *p2 = SampleCount;
        if(Timecode < *FilterTimeFrom)
        {
            *p1 = SampleCount * (*FilterTimeFrom - Timecode) / Duration;
            return; // Inside
        }
        *p1 = 0;
        return; // Intersects @From
    }

    if(Timecode > *FilterTimeTo)
    {
        *p1 = 0;
        *p2 = 0;
        return; // Outside After
    }

    if(Timecode >= *FilterTimeFrom && Endtime <= *FilterTimeTo)
    {
        *p1 = 0;
        *p2 = SampleCount;
        return; // Inside
    }

    if(Timecode < *FilterTimeFrom && Endtime > *FilterTimeFrom)
    {
        *p1 = SampleCount * (*FilterTimeFrom - Timecode) / Duration;
        if(Endtime <= *FilterTimeTo)
        {
            *p2 = SampleCount;
            return; // Intersects @From
        }
        *p2 = SampleCount * (*FilterTimeTo - Timecode) / Duration;
        return; // Intersects @From & @To
    }

    if(Timecode < *FilterTimeTo && Endtime > *FilterTimeTo)
    {
        *p2 = SampleCount * (*FilterTimeTo - Timecode) / Duration;
        if(Timecode >= *FilterTimeFrom)
        {
            *p1 = 0;
            return; // Intersects @To
        }
        *p1 = SampleCount * (*FilterTimeFrom - Timecode) / Duration;
        return; // Intersects @From & @To
    }
}

void AudioFrame::MuteClipped(int64_t* FilterTimeFrom, int64_t* FilterTimeTo)
{
    if(Timecode < *FilterTimeFrom || Timecode + Duration > *FilterTimeTo)
    {
        size_t PivotFrom;
        size_t PivotTo;
        FilterFrameIntersection(FilterTimeFrom, FilterTimeTo, &PivotFrom, &PivotTo);

        // mute sound between [0...PivotFrom]
        memset(Data, 0, PivotFrom * SampleSize);
        // keep sound between [PivotFrom...PivotTo]
        //memset(...)
        // mute sound between [PivotTo...SampleCount]
        memset(Data + (PivotTo * SampleSize), 0, (SampleCount - PivotTo) * SampleSize);

//printf("Mute: A From: 0, Count: %lu\n", (long)(PivotFrom * Pulse->FrameSize));
//printf("Mute: B From: %lu, Count: %lu\n", (long)(PivotTo * Pulse->FrameSize), (long)(Pulse->DataSize - (PivotTo * Pulse->FrameSize)));
    }
}

void AudioFrame::FadeIn(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, FadingType FadeType)
{
    if(Timecode < *FilterTimeTo)
    {
        size_t PivotFrom;
        size_t PivotTo;
        FilterFrameIntersection(FilterTimeFrom, FilterTimeTo, &PivotFrom, &PivotTo);

        // mute sound between [0...PivotFrom]
        memset(Data, 0, PivotFrom * SampleSize);

        // fade sound between [PivotFrom...PivotTo]
        int64_t ratio_num; // unfortunately we using milli seconds as resolution -> accuracy max. 1ms, but should be sufficient for fading
        int64_t ratio_den = *FilterTimeTo - *FilterTimeFrom;
        short* data_16LE = (short*)Data;
        int* data_32LE = (int*)Data;
        for(size_t sample_index=PivotFrom; sample_index<PivotTo; sample_index++) // loop all samples
        {
            for(size_t c=0; c<(size_t)ChannelCount; c++) // loop all channels
            {
                ratio_num = Timecode - *FilterTimeFrom + (Duration * (int64_t)sample_index / (int64_t)SampleCount);
                if(SampleFormatSize == 1)
                {
                    if(FadeType == FadeLinear)
                    {
                        Data[sample_index*SampleFormatSize+c] = Data[sample_index*SampleFormatSize+c] * ratio_num / ratio_den;
                    }
                    if(FadeType == FadeQuadratic)
                    {
                        Data[sample_index*SampleFormatSize+c] = Data[sample_index*SampleFormatSize+c] * ratio_num / ratio_den;
                    }
                }
                if(SampleFormatSize == 2)
                {
                    if(FadeType == FadeLinear)
                    {
                        data_16LE[sample_index*SampleFormatSize+c] = (short)(data_16LE[sample_index*SampleFormatSize+c] * ratio_num / ratio_den);
                    }
                    if(FadeType == FadeQuadratic)
                    {
                        data_16LE[sample_index*SampleFormatSize+c] = (short)(data_16LE[sample_index*SampleFormatSize+c] * ratio_num / ratio_den);
                    }
                }
                if(SampleFormatSize == 4)
                {
                    if(FadeType == FadeLinear)
                    {
                        data_32LE[sample_index*SampleFormatSize+c] = (int)(data_32LE[sample_index*SampleFormatSize+c] * ratio_num / ratio_den);
                    }
                    if(FadeType == FadeQuadratic)
                    {
                        data_32LE[sample_index*SampleFormatSize+c] = (int)(data_32LE[sample_index*SampleFormatSize+c] * ratio_num / ratio_den);
                    }
                }
            }
        }
        data_16LE = NULL;
        data_32LE = NULL;

        // keep sound between [PivotTo...SampleCount]
    }
}

void AudioFrame::FadeOut(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, FadingType FadeType)
{
    if(Timecode + Duration > *FilterTimeFrom)
    {
        size_t PivotFrom;
        size_t PivotTo;
        FilterFrameIntersection(FilterTimeFrom, FilterTimeTo, &PivotFrom, &PivotTo);

// cast data to type corresponding on f_sample_size

        // keep sound between [0...PivotFrom]
        //memset(...)
        // fade sound between [PivotFrom...PivotTo]

        // mute sound between [PivotTo...f_count]
        memset(Data + (PivotTo * SampleSize), 0, (SampleCount - PivotTo) * SampleSize);
//printf("Fade Out Mute: Frames[%lu, %lu], Time[%lu, %lu]\n", (long)0, (long)PivotFrom, (long)Timecode, (long)Timecode+Duration);
    }
}
