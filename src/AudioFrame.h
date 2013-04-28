#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include <wx/dynarray.h>

#include "Libav.h"

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
    public: int FrameSize; // in byte
    public: int SampleSize; // in byte
    public: unsigned char* Data;

    // copy all data from FrameData
    public: void FillFrame(unsigned char* FrameData);
};

WX_DEFINE_ARRAY(AudioFrame*, AudioFrameArray);

#endif // AUDIOFRAME_H
