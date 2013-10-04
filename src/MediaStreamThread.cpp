#include "MediaStreamThread.h"

MediaStreamThread::MediaStreamThread(EncodingFileLoader* SourceMedia, bool* DoStream, int64_t* ReferenceClock, long FrameIndex, long VideoStreamIndex, long AudioStreamIndex, StreamBuffer* VideoFrameBuffer, StreamBuffer* AudioFrameBuffer, int VideoTargetWidth, int VideoTargetHeight, PixelFormat VideoTargetPixelFormat) : wxThread(wxTHREAD_JOINABLE)
{
    efl = SourceMedia;
    run = DoStream;
    clock = ReferenceClock;
    vStartFrame = FrameIndex;
    vStreamIndex = VideoStreamIndex;
    aStreamIndex = AudioStreamIndex;
    vFrameBuffer = VideoFrameBuffer;
    aFrameBuffer = AudioFrameBuffer;
    vWidth = VideoTargetWidth;
    vHeight = VideoTargetHeight;
    vPixelFormat = VideoTargetPixelFormat;
    //printf("thread initialized\n");
}

MediaStreamThread::~MediaStreamThread()
{
    //printf("thread destroyed\n");
}

wxThread::ExitCode MediaStreamThread::Entry()
{
    //printf("thread started...\n");
    efl->StreamMedia(run, clock, vStartFrame, vStreamIndex, aStreamIndex, vFrameBuffer, aFrameBuffer, vWidth, vHeight, vPixelFormat);
    return (wxThread::ExitCode)0;
}
