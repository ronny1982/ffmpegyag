#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include <wx/dynarray.h>

#include "Libav.h"

enum FadingType
{
    FadeIn,
    FadeOut,
};

enum FadingCurve
{
    FadeLinear,
    FadeQuadratic,
};

class AudioFrame
{
    public: AudioFrame();
    // the pointer FrameData will be freed by this destructor, make sure not freeing it's content externally!
    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, SampleFormat FrameFormat, size_t FrameSampleCount);
    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, size_t FrameSampleCount, int Frequency);
    public: virtual ~AudioFrame();

    public: int64_t Timestamp;
    public: int64_t Timecode; // in milliseconds
    public: int64_t Duration; // in milliseconds
    public: int SampleRate;
    public: int ChannelCount;
    snd_pcm_format_t AlsaFormat;
    public: size_t SampleCount;
    public: size_t DataSize; // in byte
    // TODO: rename to something like ChannelElementSize
    public: int SampleSize; // in byte
    public: int SampleFormatSize; // in byte
    public: unsigned char* Data;

    // copy all data from FrameData
    public: void FillFrame(unsigned char* FrameData);
    // calculate p1, p2 indices of the mutual overlap of FilterTime and this AudioFrame (presented in SampleCount/SampleSize units)
    /*
     *                          |----------FilterTime----------|
     *                          :                              :
     *  |----AudioFrame----|    :                              :    |----AudioFrame----|
     *                   p1|p2  :                              :  p1|p2
     *                          :                              :
     *                |----AudioFrame----|           |----AudioFrame----|
     *                        p1|--------|p2       p1|---------|p2
     *                          :                              :
     *                    |----------------AudioFrame---------------|
     *                        p1|------------------------------|p2
     *                          :                              :
     *                          :     |----AudioFrame----|     :
     *                          :   p1|------------------|p2   :
     */
    private: void FilterFrameIntersection(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, size_t* PivotFrom, size_t* PivotTo);
    // mute samples before FilterTime, keep samples inside FilterTime, mute samples after FilterTime
    public: void MuteClipped(int64_t* FilterTimeFrom, int64_t* FilterTimeTo);
    // FadeIn: mute samples before FilterTime, fade in samples inside FilterTime, keep samples after FilterTime
    // FadeOut: keep samples before FilterTime, fade out samples inside FilterTime, mute samples after FilterTime
    public: void Fade(int64_t* FilterTimeFrom, int64_t* FilterTimeTo, FadingType FadeType, FadingCurve FadeCurve = FadeLinear);
};

WX_DEFINE_ARRAY(AudioFrame*, AudioFrameArray);

#endif // AUDIOFRAME_H
