#ifndef MEDIASTREAMTHREAD_H
#define MEDIASTREAMTHREAD_H

#include <wx/thread.h>

#include "EncodingFileLoader.h"

class MediaStreamThread : public wxThread
{
    public: MediaStreamThread(EncodingFileLoader* SourceMedia, bool* DoStream, int64_t* ReferenceClock, long FrameIndex, long VideoStreamIndex, long AudioStreamIndex, StreamBuffer* VideoFrameBuffer, StreamBuffer* AudioFrameBuffer, int VideoTargetWidth, int VideoTargetHeight, AVPixelFormat VideoTargetPixelFormat = AV_PIX_FMT_RGB24);
    public: virtual ~MediaStreamThread();

    protected: virtual ExitCode Entry();

    EncodingFileLoader* efl;
    private: bool* run;
    private: int64_t* clock;
    private: long vStartFrame;
    private: long vStreamIndex;
    private: long aStreamIndex;
    private: StreamBuffer* vFrameBuffer;
    private: StreamBuffer* aFrameBuffer;
    private: int vWidth;
    private: int vHeight;
    private: AVPixelFormat vPixelFormat;
};

#endif // MEDIASTREAMTHREAD_H
