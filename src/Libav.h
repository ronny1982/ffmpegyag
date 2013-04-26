#ifndef LIBAV_H
#define LIBAV_H

#include <wx/arrstr.h>
#include <wx/hashmap.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/choicdlg.h>
#include <wx/textdlg.h>

#include <GL/gl.h>
#include <alsa/asoundlib.h>

#ifndef INT64_C
#define INT64_C(c)  c ## L
#endif
#ifndef UINT64_C
#define UINT64_C(c) c ## UL
#endif

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

enum AVMediaFlags
{
    AVMEDIA_FLAG_NONE = 0,
    AVMEDIA_FLAG_UNKNOWN = 1,
    AVMEDIA_FLAG_VIDEO = 2, // packets contain video data (usually encoded)
    AVMEDIA_FLAG_AUDIO = 4, // packets contain audio data (usually encoded)
    AVMEDIA_FLAG_DATA = 8, // packets contain raw data (undefined)
    AVMEDIA_FLAG_SUBTITLE = 16, // packets contain subtitle data
    AVMEDIA_FLAG_ATTACHMENT = 32,
    AVMEDIA_FLAG_NB = 64,
    // common combinations
    AVMEDIA_FLAG_BASE = AVMEDIA_FLAG_VIDEO | AVMEDIA_FLAG_AUDIO,
    AVMEDIA_FLAG_COMMON = AVMEDIA_FLAG_BASE | AVMEDIA_FLAG_SUBTITLE,
    //AVMEDIA_FLAG_ADVANCED = AVMEDIA_FLAG_COMMON | AVMEDIA_FLAG_DATA,
    AVMEDIA_FLAG_ADVANCED = AVMEDIA_FLAG_COMMON | AVMEDIA_FLAG_ATTACHMENT,
    AVMEDIA_FLAG_COMPLETE = (AVMEDIA_FLAG_ADVANCED | AVMEDIA_FLAG_DATA) | AVMEDIA_FLAG_NB,
    // additional flag to mark export of image2 format sequence
    AVMEDIA_FLAG_IMG2SEQUENCE = 128
};

WX_DECLARE_STRING_HASH_MAP(wxString, StringHashMap);
WX_DECLARE_HASH_MAP(PixelFormat, wxString, wxIntegerHash, wxIntegerEqual, PixelFormatHashMap);
WX_DECLARE_HASH_MAP(CodecID, AVMediaFlags, wxIntegerHash, wxIntegerEqual, CodecIDHashMap);
WX_DECLARE_STRING_HASH_MAP(AVMediaFlags, MediaFlagHashMap);

class Libav
{
    // declare static function (fill static members with data)

    // initialize all static members with valid values
    public: static void Init();
    // converts from milliseconds to string in smpte timecode representation
    public: static wxString MilliToSMPTE(int64_t MilliSeconds);
    // converts from milliseconds to string in seconds representation (fractional)
    public: static wxString MilliToSeconds(int64_t MilliSeconds);
    // returns a list of all supported encoding viceo codecs for the given container format
    public: static wxArrayString FormatVideoCodecs(wxString ContainerFormat);
    // returns a list of all supported encoding audio codecs for the given container format
    public: static wxArrayString FormatAudioCodecs(wxString ContainerFormat);
    // returns a list of all supported encoding subtitle codecs for the given container format
    public: static wxArrayString FormatSubtitleCodecs(wxString ContainerFormat);

    // declare static members

    // the path to the best matching ffmpeg binary found by init()
    public: static wxFileName ConverterApplication;
    // supported codecs for video encoding
    public: static wxArrayString VideoCodecList;
    // supported codecs for audio encoding
    public: static wxArrayString AudioCodecList;
    // supported codecs for subtitle encoding
    public: static wxArrayString SubtitleCodecList;
    // supported container formats for muxing
    public: static wxArrayString FormatList;
    // extensions associated with container format
    public: static StringHashMap FormatExtensionMap; // wxString FileFormat -> wxString FileExtension
    // media types associated with container format
    public: static MediaFlagHashMap FormatMediaMap; // wxString FileFormat -> AVMediaFlags AVMEDIA_FLAG_*
    // media types associated with codec id
    private: static CodecIDHashMap CodecMediaMap; // CodecID CODEC_ID_* -> AVMediaFlags AVMEDIA_FLAG_*
    // human readable pixel format associated with PIX_FMT_*
    public: static PixelFormatHashMap PixelDescriptionMap; // PixelFormat PIX_FMT_* -> wxString PixelDescription
    // human readable picture type
    public: static wxString GetPicType(AVPictureType PicType);
    // convert AVPixelFormat to GL Format
    public: static GLint GetGLFormat(PixelFormat PixFormat);
    // convert AVSampleFormat to Alsa Format
    public: static snd_pcm_format_t GetAlsaFormat(SampleFormat SplFormat);
};

#endif // LIBAV_H
