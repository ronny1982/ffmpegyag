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
    // the pointer FrameData will be freed by this destructor, make sure not freeing it's content externally!
    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, AVSampleFormat FrameSampleFormat, size_t FrameSampleCount);
    public: virtual ~AudioFrame();

    public: int64_t Timestamp;
    public: int64_t Timecode; // in milliseconds
    public: int64_t Duration; // in milliseconds
    public: int SampleRate;
    // Number of channels (e.g. 3)
    public: int ChannelCount;
    // Number format of a single sample (e.g. 16bit -> 2 byte)
    AVSampleFormat PCMFormat;
    // Number of samples per channel (e.g. 8)
    public: size_t SampleCount;
    // Overall size of all channels (e.g. 48 byte)
    public: size_t DataSize;
    // Overall size of a single channel (e.g. 16 byte)
    public: int ChannelSize;
    // Size of a single sample (including all channels) [in byte]
    public: int SampleSize;
    // Size of a single sample (e.g. 2 byte)
    public: int SampleFormatSize;
    // Contains INTERLEAVED audio data for all channels
    public: unsigned char* Data;

    // copy all data from FrameData
    public: void FillFrame(unsigned char** FrameData);
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
    // mix all channels into front-let & front-right
    public: void MixDown();
};

WX_DEFINE_ARRAY(AudioFrame*, AudioFrameArray);

#endif // AUDIOFRAME_H
