#include "VideoFrame.h"

VideoFrame::VideoFrame()
{
    Timestamp = int64_t(0);
    Timecode = int64_t(0);
    Duration = int64_t(0);
    Width = 32;
    Height = 32;
    PicFormat = PIX_FMT_RGB24;
    PicType = Libav::GetPicType(AV_PICTURE_TYPE_I);
    DataSize = avpicture_get_size(PicFormat, Width, Height);
    Data = (unsigned char*)av_malloc(DataSize);
    // black frame
    for(size_t i=0; i<DataSize; i++)
    {
        Data[i] = (unsigned char)0;
    }
}

VideoFrame::VideoFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameWidth, int FrameHeight, PixelFormat FrameFormat, AVPictureType FrameType)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    Width = FrameWidth;
    Height = FrameHeight;
    PicFormat = FrameFormat;
    PicType = Libav::GetPicType(FrameType);
    DataSize = avpicture_get_size(FrameFormat, FrameWidth, FrameHeight);
    Data = (unsigned char*)av_malloc(DataSize);
}

VideoFrame::VideoFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameWidth, int FrameHeight, AVPictureType FrameType, unsigned char Red, unsigned char Green, unsigned char Blue)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    Width = FrameWidth;
    Height = FrameHeight;
    PicFormat = PIX_FMT_RGB24;
    PicType = Libav::GetPicType(FrameType);
    DataSize = avpicture_get_size(PicFormat, FrameWidth, FrameHeight);
    Data = (unsigned char*)av_malloc(DataSize);

    for(size_t i=0; i<DataSize; i+=3)
    {
        Data[i+0] = Red;
        Data[i+1] = Green;
        Data[i+2] = Blue;
    }
}

VideoFrame::~VideoFrame()
{
    //wxDELETEA(Data);
    av_free(Data);
    Data = NULL;
}

void VideoFrame::FillFrame(unsigned char* FrameData)
{
    memcpy(Data, FrameData, DataSize);
}
