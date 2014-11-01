#include "AudioFrame.h"

AudioFrame::AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, AVSampleFormat FrameSampleFormat, size_t FrameSampleCount)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    SampleRate = FrameSampleRate;
    ChannelCount = FrameChannels;
    PCMFormat = FrameSampleFormat;
    SampleCount = FrameSampleCount;
    DataSize = av_samples_get_buffer_size(NULL, FrameChannels, FrameSampleCount, PCMFormat, 1);
    ChannelSize = DataSize / ChannelCount;
    SampleSize = DataSize / SampleCount;
    SampleFormatSize = SampleSize / ChannelCount;
    Data = (unsigned char*)av_malloc(DataSize);
}

AudioFrame::~AudioFrame()
{
    av_free(Data);
    Data = NULL;
}

void AudioFrame::FillFrame(unsigned char** FrameData)
{
    if(av_sample_fmt_is_planar(PCMFormat) > 0)
    {
        // Convert non-interleaved data to interleaved data
        // TODO: Is ordering of channels correct?
        // [ L L L L R R R R C C C C ] -> [ L R C L R C L R C L R C ]
        for(size_t s=0, b=0, so=0; s<SampleCount; s++)
        {
            so = s*SampleFormatSize;
            for(int c=0; c<ChannelCount; c++)
            {
                for(int f=0; f<SampleFormatSize; f++)
                {
                    // FrameData only holds a maximum of AV_NUM_DATA_POINTERS planes(channels)
                    if(c < AV_NUM_DATA_POINTERS)
                    {
                        Data[b] = FrameData[c][so+f];
                    }
                    else
                    {
                        Data[b] = 0;
                    }
                    b++;
                }
            }
        }
    }
    else
    {
        memcpy(Data, FrameData[0], DataSize);
    }
}

void AudioFrame::FilterFrameIntersection(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, size_t* p1, size_t* p2)
{
    int64_t Endtime = Timecode + Duration;

    // TODO (ronny#medium#): verify all conditions for correctness, unit testing?

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

    // this audio packet lies completely inside the filter range
    if(Timecode >= *FilterTimeFrom && Endtime <= *FilterTimeTo)
    {
        *p1 = 0;
        *p2 = SampleCount;
        return; // Inside
    }

    if(Timecode <= *FilterTimeFrom && Endtime >= *FilterTimeFrom)
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

    if(Timecode <= *FilterTimeTo && Endtime >= *FilterTimeTo)
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

    printf("ERROR AudioFrame::FilterFrameIntersection(...): No appropriate audio packet pivots found!\n");
    *p1 = 0;
    *p2 = SampleCount;
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
    }
}

void AudioFrame::Fade(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, FadingType FadeType, FadingCurve FadeCurve)
{
    if((FadeType == FadeIn && Timecode < *FilterTimeTo) || (FadeType == FadeOut && Timecode + Duration > *FilterTimeFrom))
    {
        size_t PivotFrom;
        size_t PivotTo;
        FilterFrameIntersection(FilterTimeFrom, FilterTimeTo, &PivotFrom, &PivotTo);

        if(FadeType == FadeIn)
        {
            // mute sound between [0...PivotFrom]
            memset(Data, 0, PivotFrom * SampleSize);
        }
        // keep sound between [0...PivotFrom]

        // fade sound between [PivotFrom...PivotTo]
        // unfortunately we using milli seconds as resolution -> accuracy max. 1ms, but should be sufficient for fading
        int64_t ratio_den = *FilterTimeTo - *FilterTimeFrom;
        int64_t ratio_num = ratio_den;
        short* data_16 = (short*)Data;
        int* data_32 = (int*)Data;
        float* data_f = (float*)Data;
        double* data_d = (double*)Data;
        size_t index;
        for(size_t sample_index=PivotFrom; sample_index<PivotTo; sample_index++) // loop all samples
        {
            if(FadeType == FadeIn)
            {
                ratio_num = Timecode - *FilterTimeFrom + (Duration * (int64_t)sample_index / (int64_t)SampleCount);
            }
            if(FadeType == FadeOut)
            {
                ratio_num = Timecode - *FilterTimeTo + (Duration * (int64_t)sample_index / (int64_t)SampleCount);
            }

            for(size_t c=0; c<(size_t)ChannelCount; c++) // loop all channels
            {
                // NOTE: non-interleaved (planar) formats can be treated as interleaved data,
                // because it was converted during the assignment (FillFrame(*data))
                index = sample_index * ChannelCount + c;

                if(PCMFormat == AV_SAMPLE_FMT_U8 || PCMFormat == AV_SAMPLE_FMT_U8P)
                {
                    if(FadeCurve == FadeLinear)
                    {
                        Data[index] = (unsigned char)(Data[index] * ratio_num / ratio_den);
                    }
                    if(FadeCurve == FadeQuadratic)
                    {
                        Data[index] = (unsigned char)(Data[index] * ratio_num / ratio_den);
                    }
                }
                if(PCMFormat == AV_SAMPLE_FMT_S16 || PCMFormat == AV_SAMPLE_FMT_S16P)
                {
                    if(FadeCurve == FadeLinear)
                    {
                        data_16[index] = (short)(data_16[index] * ratio_num / ratio_den);
                    }
                    if(FadeCurve == FadeQuadratic)
                    {
                        data_16[index] = (short)(data_16[index] * ratio_num / ratio_den);
                    }
                }
                if(PCMFormat == AV_SAMPLE_FMT_S32 || PCMFormat == AV_SAMPLE_FMT_S32P)
                {
                    if(FadeCurve == FadeLinear)
                    {
                        data_32[index] = (int)(data_32[index] * ratio_num / ratio_den);
                    }
                    if(FadeCurve == FadeQuadratic)
                    {
                        data_32[index] = (int)(data_32[index] * ratio_num / ratio_den);
                    }
                }
                if(PCMFormat == AV_SAMPLE_FMT_FLT || PCMFormat == AV_SAMPLE_FMT_FLTP)
                {
                    if(FadeCurve == FadeLinear)
                    {
                        data_f[index] = (float)(data_f[index] * ((float)ratio_num / (float)ratio_den));
                    }
                    if(FadeCurve == FadeQuadratic)
                    {
                        data_f[index] = (float)(data_f[index] * ((float)ratio_num / (float)ratio_den));
                    }
                }
                if(PCMFormat == AV_SAMPLE_FMT_DBL || PCMFormat == AV_SAMPLE_FMT_DBLP)
                {
                    if(FadeCurve == FadeLinear)
                    {
                        data_d[index] = (double)(data_d[index] * ((double)ratio_num / (double)ratio_den));
                    }
                    if(FadeCurve == FadeQuadratic)
                    {
                        data_d[index] = (double)(data_d[index] * ((double)ratio_num / (double)ratio_den));
                    }
                }
            }
        }
        data_16 = NULL;
        data_32 = NULL;
        data_f = NULL;
        data_d = NULL;

        if(FadeType == FadeOut)
        {
            // mute sound between [PivotTo...SampleCount]
            memset(Data + (PivotTo * SampleSize), 0, (SampleCount - PivotTo) * SampleSize);
        }
        // keep sound between [PivotTo...SampleCount]
    }
}

void AudioFrame::MixDown()
{
    if(ChannelCount > 2)
    {
        short* data_16 = (short*)Data;
        int* data_32 = (int*)Data;
        float* data_f = (float*)Data;
        double* data_d = (double*)Data;
        size_t index;
        size_t index_center_channel;
        for(size_t sample_index=0; sample_index<SampleCount; sample_index++) // loop all samples
        {
            // NOTE: non-interleaved (planar) formats can be treated as interleaved data,
            // because it was converted during the assignment (FillFrame(*data))

            index = sample_index*ChannelCount;
            // NOTE: Order of interleaved channels -> Front_L, Front_R, Center, LowFreq, Side_L, Side_R, Back_L, Back_R
            index_center_channel = 2;

            if(PCMFormat == AV_SAMPLE_FMT_U8 || PCMFormat == AV_SAMPLE_FMT_U8P)
            {
                Data[index+0] = (unsigned char)((Data[index+0] + Data[index+index_center_channel]) / 2); // center ++> left
                Data[index+1] = (unsigned char)((Data[index+1] + Data[index+index_center_channel]) / 2); // center ++> right
            }
            if(PCMFormat == AV_SAMPLE_FMT_S16 || PCMFormat == AV_SAMPLE_FMT_S16P)
            {
                data_16[index+0] = (short)((data_16[index+0] + data_16[index+index_center_channel]) / 2); // center ++> left
                data_16[index+1] = (short)((data_16[index+1] + data_16[index+index_center_channel]) / 2); // center ++> right
            }
            if(PCMFormat == AV_SAMPLE_FMT_S32 || PCMFormat == AV_SAMPLE_FMT_S32P)
            {
                data_32[index+0] = (int)((data_32[index+0] + data_32[index+index_center_channel]) / 2); // center ++> left
                data_32[index+1] = (int)((data_32[index+1] + data_32[index+index_center_channel]) / 2); // center ++> right
            }
            if(PCMFormat == AV_SAMPLE_FMT_FLT || PCMFormat == AV_SAMPLE_FMT_FLTP)
            {
                data_f[index+0] = (float)((data_f[index+0] + data_f[index+index_center_channel]) / 2); // center ++> left
                data_f[index+1] = (float)((data_f[index+1] + data_f[index+index_center_channel]) / 2); // center ++> right
            }
            if(PCMFormat == AV_SAMPLE_FMT_DBL || PCMFormat == AV_SAMPLE_FMT_DBLP)
            {
                data_d[index+0] = (double)((data_d[index+0] + data_d[index+index_center_channel]) / 2); // center ++> left
                data_d[index+1] = (double)((data_d[index+1] + data_d[index+index_center_channel]) / 2); // center ++> right
            }
        }

        data_16 = NULL;
        data_32 = NULL;
        data_f = NULL;
        data_d = NULL;
    }
}
