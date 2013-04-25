#ifndef VIDEOFRAMEGOP_H
#define VIDEOFRAMEGOP_H

#include "VideoFrame.h"

class VideoFrameGOP
{
    public: VideoFrameGOP();
    public: VideoFrameGOP(int Uid);
    public: virtual ~VideoFrameGOP();

    private: int ID;
    private: VideoFrameArray VideoFrames;

    // get the number of frames in gop
    public: size_t GetCount();
    // clear all data (including id)
    public: void Flush();
    // returns the identifier for this gop (usually keyframe-index or keyframe-timestamp)
    public: int GetID();
    // change the id of this gop (usually keyframe-index or keyframe-timestamp)
    public: void SetID(int uid);
    // returns the timestamp of first video frame in gop (usually keyframe)
    public: int64_t GetFirstTimestamp();
    // returns the timestamp of last video frame in gop
    public: int64_t GetLastTimestamp();
    // check if the timestamp can be found inside the gop
    public: bool ContainsTimestamp(int64_t Timestamp);
    // append a video frame to the gop
    // the destruction of *Frame will be performed by GOP
    public: void AddVideoFrame(VideoFrame* Frame);
    // return the video frame from the gop which is closest to the given timestamp
    public: VideoFrame* GetVideoFrame(int64_t Timestamp);
};

#endif // VIDEOFRAMEGOP_H
