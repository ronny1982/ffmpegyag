#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include <alsa/asoundlib.h>
#include <wx/dynarray.h>

#include "Libav.h"

class AudioFrame
{
    public: AudioFrame();
    // the pointer FrameData will be freed by this destructor, make sure not freeing it's content externally!
    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, SampleFormat FrameFormat, int FrameSampleCount);
    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameSampleRate, int FrameChannels, int FrameSampleCount, int Frequency);
    public: virtual ~AudioFrame();

    public: int64_t Timestamp;
    public: int64_t Timecode; // in milliseconds
    public: int64_t Duration; // in milliseconds
    public: int SampleRate;
    public: int Channels;
    SampleFormat AVFormat;
    public: int SampleCount;
    public: size_t DataSize;
    public: unsigned char* Data;

    // copy all data from FrameData
    public: void FillFrame(unsigned char* FrameData);
    public: snd_pcm_format_t GetPCMFormat();
};

WX_DEFINE_ARRAY(AudioFrame*, AudioFrameArray);

#endif // AUDIOFRAME_H
