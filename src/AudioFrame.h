#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include <alsa/asoundlib.h>

#include "Libav.h"

class AudioFrame
{
    public: AudioFrame();
    // copy constructor to clone pointer data instead of assigning pointers to the same data
    // prevent deletion of data where multiple copies are pointing to the same data...
    //public: AudioFrame(const AudioFrame&);
    // the pointer FrameData will be freed by this destructor, make sure not freeing it's content externally!
//    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int FrameWidth, int FrameHeight, PixelFormat FrameFormat, AVPictureType FrameType, unsigned char* FrameData);
//    public: AudioFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int FrameWidth, int FrameHeight, AVPictureType FrameType, unsigned char Red, unsigned char Green, unsigned char Blue);
    public: virtual ~AudioFrame();

    public: int64_t Timestamp;
    public: int64_t Timecode; // in milliseconds
    public: int64_t Duration; // in milliseconds
    // samplerate
    // channels
    SampleFormat AVFormat;

    public: size_t DataSize;
    public: unsigned char* Data;

    public: snd_pcm_format_t GetPCMFormat();
};

#endif // AUDIOFRAME_H
