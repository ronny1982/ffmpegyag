#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <wx/dynarray.h>

#include "Libav.h"

class VideoFrame
{
    public: VideoFrame();
    // the pointer FrameData will be freed by this destructor, make sure not freeing it's content externally!
    public: VideoFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameWidth, int FrameHeight, PixelFormat FrameFormat, AVPictureType FrameType);
    public: VideoFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameWidth, int FrameHeight, AVPictureType FrameType, unsigned char Red, unsigned char Green, unsigned char Blue);
    public: virtual ~VideoFrame();

    public: int64_t Timestamp;
    public: int64_t Timecode; // in milliseconds
    public: int64_t Duration; // in milliseconds
    public: int Width;
    public: int Height;
    public: GLint GLFormat;
    public: PixelFormat PicFormat;
    public: wxString PicType;
    public: size_t DataSize;
    public: unsigned char* Data;

    // copy all data from FrameData
    public: void FillFrame(unsigned char* FrameData);
};

WX_DEFINE_ARRAY(VideoFrame*, VideoFrameArray);

#endif // VIDEOFRAME_H
