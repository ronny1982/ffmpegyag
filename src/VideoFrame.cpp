#include "VideoFrame.h"

VideoFrame::VideoFrame()
{
    Timestamp = int64_t(0);
    Timecode = int64_t(0);
    Duration = int64_t(0);
    Width = 32;
    Height = 32;
    AVFormat = PIX_FMT_RGB24;
    AVType = AV_PICTURE_TYPE_I;
    DataSize = avpicture_get_size(AVFormat, Width, Height);
    Data = (unsigned char*)av_malloc(DataSize);
    // black frame
    for(size_t i=0; i<DataSize; i++)
    {
        Data[i] = (unsigned char)0;
    }
}

VideoFrame::VideoFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameWidth, int FrameHeight, PixelFormat FrameFormat, AVPictureType FrameType, size_t FrameDataSize, unsigned char* FrameData)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    Width = FrameWidth;
    Height = FrameHeight;
    AVFormat = FrameFormat;
    AVType = FrameType;
    DataSize = FrameDataSize;
    Data = FrameData;
}

VideoFrame::VideoFrame(int64_t FrameTimestamp, int64_t FrameTimecode, int64_t FrameDuration, int FrameWidth, int FrameHeight, AVPictureType FrameType, unsigned char Red, unsigned char Green, unsigned char Blue)
{
    Timestamp = FrameTimestamp;
    Timecode = FrameTimecode;
    Duration = FrameDuration;
    Width = FrameWidth;
    Height = FrameHeight;
    AVFormat = PIX_FMT_RGB24;
    AVType = FrameType;
    DataSize = avpicture_get_size(AVFormat, Width, Height);
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

GLint VideoFrame::GetGLFormat()
{
    // TODO: add more formats
    switch(AVFormat)
    {
        case PIX_FMT_RGB24: return GL_RGB;
        default: return 0;
    }
}

wxString VideoFrame::GetPicType()
{
    switch(AVType)
    {
        case AV_PICTURE_TYPE_I: return wxT("I");
        case AV_PICTURE_TYPE_P: return wxT("P");
        case AV_PICTURE_TYPE_B: return wxT("B");
        case AV_PICTURE_TYPE_S: return wxT("S");
        case AV_PICTURE_TYPE_SI: return wxT("i");
        case AV_PICTURE_TYPE_SP: return wxT("p");
        case AV_PICTURE_TYPE_BI: return wxT("b");
        default: return wxT("?");
    }
}
