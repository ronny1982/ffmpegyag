#ifndef ENCODINGTASK_H
#define ENCODINGTASK_H

#include "EncodingFileLoader.h"
#include "EncodingFileSaver.h"

enum Pass
{
    NoPass, // No-Pass processing (default)
    FirstPass, // Two-Pass first pass
    SecondPass // Two-Pass seconf pass
};

class FileSegment
{
    public: FileSegment(wxFileName FileOut, int64_t StartTime, int64_t EndTime);
    public: virtual ~FileSegment();

    wxFileName OutputFile; // file where the segment will be stored
    public: int64_t TimeFrom; // start time in milli seconds
    public: int64_t TimeTo; // end time in milli seconds
    // filter times are relative inside segments!
    public: int64_t FilterVideoFadeInStart; // fade in start time in milli seconds (relative to segment start)
    public: int64_t FilterVideoFadeInDuration; // fade in duration for video in milli seconds
    public: int64_t FilterVideoFadeOutStart; // fade out start time in milli seconds (relative to segment start)
    public: int64_t FilterVideoFadeOutDuration; // fade out duration for video in milli seconds
    public: int64_t FilterAudioFadeInStart; // fade in start time in milli seconds (relative to segment start)
    public: int64_t FilterAudioFadeInDuration; // fade in duration for audio in milli seconds
    public: int64_t FilterAudioFadeOutStart; // fade out start time in milli seconds (relative to segment start)
    public: int64_t FilterAudioFadeOutDuration; // fade out duration for audio in milli seconds

    /*
    public: int64_t GetTimeFrom();
    public: void SetTimeFrom(int64_t StartTime);
    public: int64_t GetTimeTo();
    public: void SetTimeTo(int64_t EndTime);
    */
    public: int64_t GetDuration();
};

WX_DEFINE_ARRAY(FileSegment*, FileSegmentArray);

class EncodingTask
{
    public: EncodingTask();
    public: virtual ~EncodingTask();

    public: EncodingFileLoaderArray InputFiles;
    public: wxFileName OutputFile;
    public: wxString OutputFormat;
    public: FileSegmentArray OutputSegments;
    // if task contains more han one segment, set this option true to concat the segments into a single file
    public: bool OutputSegmentsConcat;
    public: bool TwoPass;
    public: bool RemoveMetadata;
    public: bool RemoveChapters;

    // search through all selected streams and return the muxed duration
    // requires that all streams timestamps are shifted regarding the other streams (no single stream shifting)
    // use UnEnabled=true to include not enabled streams, use UnEnabled=false to consider only enabled streams
    // use Longest=true to get longest stream duration, or Longest=false to get shortest stream duration
    public: int64_t GetMultiplexDuration(bool IncludeVideoStreams = true, bool IncludeAudioStreams = true, bool UnEnabled = true, bool Longest = true);
    // return the commands for this encoding task (number depending on segments & multipass count)
    public: wxArrayString GetCommands();
    // return the command for use with avconv
    private: wxString GetCommandAVConv(FileSegment* Segment, Pass PassNumber = NoPass);
};

WX_DEFINE_ARRAY(EncodingTask*, EncodingTaskArray);

#endif // ENCODINGTASK_H
