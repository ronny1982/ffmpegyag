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

struct Range
{
    int64_t From; // start time in milli seconds
    int64_t To; // end time in milli seconds

    public: int64_t GetDuration();
};

class FileSegment
{
    public: FileSegment(wxFileName FileOut, int64_t StartTime, int64_t EndTime);
    public: virtual ~FileSegment();

    wxFileName OutputFile; // file where the segment will be stored
    Range Time;
    Range VideoFadeIn; // relative to segment time
    Range VideoFadeOut; // relative to segment time
    Range AudioFadeIn; // relative to segment time
    Range AudioFadeOut; // relative to segment time
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
