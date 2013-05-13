#ifndef ENCODINGFILELOADER_H
#define ENCODINGFILELOADER_H

#include <wx/progdlg.h>

#include "AudioFrame.h"
#include "VideoFrameGOP.h"
#include "EncodingMediaStreams.h"
#include "StreamBuffer.h"

class EncodingFileLoader
{
    public: EncodingFileLoader(wxFileName InputFile);
    public: virtual ~EncodingFileLoader();

    public: wxFileName File;
    private: VideoFrameGOP GOPBuffer;
    // contains the timestamps for each frame of each video stream, extends the build in keyframe index: pFormatCtx->streams[i]->index_entries.timestamp
    private: AVFormatContext *pFormatCtx;
    private: bool Locked;

    public: int64_t FileSize; // filesize in byte
    public: int64_t FileDuration; // shared duration of all streams in milli seconds
    public: VideoStreamArray VideoStreams;
    public: AudioStreamArray AudioStreams;
    public: SubtitleStreamArray SubtitleStreams;

    // check if this file can be processed by libav
    public: bool IsOpen();
    // check if the reader is currently busy (reading in progress)
    public: bool IsLocked();
    // clear the shared av buffer and reset gop buffer
    public: void FlushBuffer();
    // returns the estimaded frame number of a stream
    private: int64_t GetStreamEstimatedFrameCount(unsigned int StreamIndex);
    // return the closest keyframe before the given index
    private: long SeekKeyFrameIndex(long VideoStreamIndex, long FrameIndex);
    // set the file pointer to the given KeyFrameIndex¹ (considering video and audio stream)
    // ¹when VideoStreamIndex > -1 && AudioStreamIndex > -1 then KeyFrameIndex must be from VideoStream!
    private: bool SetStreamPosition(long VideoStreamIndex, long AudioStreamIndex, long KeyFrameIndex);
    // returns the time (milliseconds) for a given frame number in a video stream
    public: int64_t GetTimeFromFrameV(long VideoStreamIndex, long FrameIndex);
    // returns the frame number for a given timestamp in a video stream
    public: long GetFrameFromTimestampV(long VideoStreamIndex, int64_t Timestamp);
    // returns the frame number for a given timestamp in an audio stream
    public: long GetFrameFromTimestampA(long AudioStreamIndex, int64_t Timestamp);
    // returns the frame number for a given time (milliseconds) in a video stream
    public: long GetFrameFromTimeV(long VideoStreamIndex, int64_t Time);
    // returns the time (milliseconds) for a given timestamp in a video stream
    private: int64_t GetTimeFromTimestampV(long VideoStreamIndex, int64_t Timestamp);
    // returns the time (milliseconds) for a given timestamp in a audio stream
    private: int64_t GetTimeFromTimestampA(long AudioStreamIndex, int64_t Timestamp);
    // returns the timestamp for a given time in milliseconds in a video stream
    private: int64_t GetTimestampFromTimeV(long VideoStreamIndex, int64_t Time);
    // returns the byte position for a given timestamp in an audio stream
    public: IndexEntry* GetIndexEntryFromTimestampA(long AudioStreamIndex, int64_t Timestamp);
    // returns the raw image data of the selected stream and frame number
    // do not delete VideoFrame*, this pointer is freed by GOPBuffer
    public: VideoFrame* GetVideoFrameData(long FrameIndex, long VideoStreamIndex, int TargetWidth, int TargetHeight, PixelFormat TargetPixelFormat = PIX_FMT_RGB24);
    //public: AudioFrame* GetAudioFrameData(long AudioStreamIndex, long FrameIndex, int TargetChannels, int TargetSamplerate, SampleFormat TargetSampleFormat = AV_SAMPLE_FMT_S16);
    // stream decoded audio/video frames into the fifo buffer
    public: void StreamMedia(bool* DoStream, int64_t* ReferenceClock,
                            long FrameIndex, long VideoStreamIndex, long AudioStreamIndex,
                            StreamBuffer* VideoFrameBuffer, StreamBuffer* AudioFrameBuffer,
                            int VideoTargetWidth, int VideoTargetHeight,
                            PixelFormat VideoTargetPixelFormat = PIX_FMT_RGB24);
};

WX_DEFINE_ARRAY(EncodingFileLoader*, EncodingFileLoaderArray);

#endif // ENCODINGFILELOADER_H
