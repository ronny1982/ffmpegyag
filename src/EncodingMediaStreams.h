#ifndef ENCODINGMEDIATREAMS_H
#define ENCODINGMEDIATREAMS_H

#include <wx/dynarray.h>

#include "Libav.h"
#include "EncodingSettings.h"

struct IndexEntry
{
    public: IndexEntry(int64_t PacketTimestamp, int64_t PacketPosition, bool PacketKeyframe);
    public: virtual ~IndexEntry();

    int64_t Timestamp;
    int64_t Position;
    bool Keyframe;
};

WX_DEFINE_ARRAY(IndexEntry*, IndexEntryArray);

class MediaStream
{
    public: MediaStream();
    public: MediaStream(unsigned int StreamID, bool EnableStream);
    public: virtual ~MediaStream();

    public: unsigned int ID;
    public: size_t FrameCount;
    public: IndexEntryArray IndexEntries;
    public: bool Enabled; // set to true if this stream should be included into the output file
    public: int64_t Size; // byte
    public: int64_t StartTime; // milli seconds
    public: int64_t Duration; // milli seconds
    public: int Bitrate; // bit/sec
    public: wxString Title;
    public: wxString Language;
    public: wxString CodecName; // short name of codec
};

class VideoStream : public MediaStream
{
    public: VideoStream(unsigned int StreamID, bool EnableStream);
    public: virtual ~VideoStream();

    public: double FrameRate;
    public: int Width;
    public: int Height;
    //public: enum AVPixelFormat PixFormat;
    public: wxString Profile; // BitDepth, PixelFormat(YUV, RGB,...), Level
    public: VideoSettings EncodingSettings;
};

WX_DEFINE_ARRAY(VideoStream*, VideoStreamArray);

class AudioStream : public MediaStream
{
    public: AudioStream(unsigned int StreamID, bool EnableStream);
    public: virtual ~AudioStream();

    public: int SampleRate;
    public: int ChannelCount;
    public: enum AVSampleFormat SampleFormat;
    public: AudioSettings EncodingSettings;
};

WX_DEFINE_ARRAY(AudioStream*, AudioStreamArray);

class SubtitleStream : public MediaStream
{
    public: SubtitleStream(unsigned int StreamID, bool EnableStream);
    public: virtual ~SubtitleStream();

    public: SubtitleSettings EncodingSettings;
};

WX_DEFINE_ARRAY(SubtitleStream*, SubtitleStreamArray);

#endif // ENCODINGMEDIATREAMS_H
