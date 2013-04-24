#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include <alsa/asoundlib.h>
#include <wx/dynarray.h>

#include "Libav.h"

class AudioFrame
{
    public: AudioFrame();
    // the pointer FrameData will be freed by this destructor, make sure not freeing it's content externally!

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

WX_DEFINE_ARRAY(AudioFrame*, AudioFrameArray);

#endif // AUDIOFRAME_H
