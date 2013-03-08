#ifndef ENCODINGFILELOADER_H
#define ENCODINGFILELOADER_H

#include <wx/file.h>
#include <wx/filename.h>
#include <wx/progdlg.h>

#include "VideoFrameGOP.h"
#include "EncodingMediaStreams.h"

class EncodingFileLoader
{
    public: EncodingFileLoader(wxFileName InputFile);
    public: virtual ~EncodingFileLoader();

    public: wxFileName File;
    private: VideoFrameGOP GOPBuffer;
    // contains the timestamps for each frame of each video stream, extends the build in keyframe index: pFormatCtx->streams[i]->index_entries.timestamp
    private: AVFormatContext *pFormatCtx;

    public: int64_t FileSize; // filesize in byte
    public: int64_t FileDuration; // shared duration of all streams in milli seconds
    public: VideoStreamArray VideoStreams;
    public: AudioStreamArray AudioStreams;
    public: SubtitleStreamArray SubtitleStreams;

    // check if this file can be processed by libav
    public: bool CanRead();
    // clear the shared av buffer and reset gop buffer
    public: void FlushBuffer();
    // returns the estimaded frame number of a stream
    private: int64_t GetStreamEstimatedFrameCount(unsigned int StreamIndex);
    // set the file pointer to the closest keyframe before the given index
    private: long SeekKeyFrameIndex(long VideoStreamIndex, long FrameIndex);
    // set the file pointer to the closest keyframe before the given index
    private: bool SetStreamPosition(long VideoStreamIndex, long KeyFrameIndex);
    // returns the time (milliseconds) for a specific frame in a video stream
    public: int64_t GetTimeFromFrame(long VideoStreamIndex, long FrameIndex);
    // returns the time in milliseconds for a given timestamp of a stream
    private: int64_t GetTimeFromTimestamp(long VideoStreamIndex, int64_t Timestamp);
    // returns the timestamp for a given time in milliseconds of a stream
    private: int64_t GetTimestampFromTime(long VideoStreamIndex, int64_t Time);
    // returns the raw image data of the selected stream and frame number
    // do not delete VideoFrame*, this pointer is freed by GOPBuffer
    public: VideoFrame* GetVideoFrameData(long VideoStreamIndex, long FrameIndex, int TargetWidth, int TargetHeight, PixelFormat TargetPixelFormat = PIX_FMT_RGB24);
};

WX_DEFINE_ARRAY(EncodingFileLoader*, EncodingFileLoaderArray);

#endif // ENCODINGFILELOADER_H
