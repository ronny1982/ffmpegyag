#include "Libav.h"

// define static members

wxFileName Libav::ConverterApplication;
wxArrayString Libav::VideoCodecList;
wxArrayString Libav::AudioCodecList;
wxArrayString Libav::SubtitleCodecList;
wxArrayString Libav::FormatList;
StringHashMap Libav::FormatExtensionMap;
MediaFlagHashMap Libav::FormatMediaMap;
CodecIDHashMap Libav::CodecMediaMap;
PixelFormatHashMap Libav::PixelDescriptionMap;

// initialize static members inside this static function

void Libav::Init()
{
    av_register_all();

    // find converter application (in the application directory!)

    ConverterApplication.Assign(wxStandardPaths::Get().GetExecutablePath()); // this will also set extension!

    wxArrayString ConverterFiles;
    wxArrayString ConverterLabels;
    wxDir::GetAllFiles(ConverterApplication.GetPath(), &ConverterFiles, wxT("ffmpeg*"), wxDIR_FILES);
    wxDir::GetAllFiles(ConverterApplication.GetPath(), &ConverterFiles, wxT("avconv*"), wxDIR_FILES);

    // remove ffmpegyag itself from the list
    for(long f=0; f<(long)ConverterFiles.GetCount(); f++)
    {
        if(ConverterFiles[f].IsSameAs(ConverterApplication.GetFullPath()))
        {
            ConverterFiles.RemoveAt(f);
            f--;
        }
    }

    #ifdef __LINUX__

        // search linux system paths, when no converter in the application directory was found
        if(ConverterFiles.GetCount() < 1)
        {
            //wxDir::GetAllFiles(wxT("/bin"), &ConverterFiles, wxT("ffmpeg*"), wxDIR_FILES);
            //wxDir::GetAllFiles(wxT("/bin"), &ConverterFiles, wxT("avconv*"), wxDIR_FILES);
            wxDir::GetAllFiles(wxT("/usr/bin"), &ConverterFiles, wxT("ffmpeg*"), wxDIR_FILES);
            wxDir::GetAllFiles(wxT("/usr/bin"), &ConverterFiles, wxT("avconv*"), wxDIR_FILES);
            //wxDir::GetAllFiles(wxT("/usr/local/bin"), &ConverterFiles, wxT("ffmpeg*"), wxDIR_FILES);
            //wxDir::GetAllFiles(wxT("/usr/local/bin"), &ConverterFiles, wxT("avconv*"), wxDIR_FILES);

            // remove ffmpegyag itself from the list
            for(long f=0; f<(long)ConverterFiles.GetCount(); f++)
            {
                if(ConverterFiles[f].AfterLast(wxFileName::GetPathSeparator()).IsSameAs(ConverterApplication.GetFullName()))
                {
                    ConverterFiles.RemoveAt(f);
                    f--;
                }
            }
        }

    #endif // LINUX

    // add found applications to a selection list for the user to choose
    for(long f=0; f<(long)ConverterFiles.GetCount(); f++)
    {
        ConverterLabels.Add(ConverterFiles[f]);
        //ConverterLabels.Add(ConverterFiles[f].AfterLast(wxFileName::GetPathSeparator()));
    }

    if(ConverterFiles.GetCount() > 1)
    {
        wxSingleChoiceDialog win(NULL, wxT("Multiple video converters have been found in the application directory.\nPlease select your prefered video converter:"), wxT("Select Video Converter"), ConverterLabels);
        win.SetSelection(0);
        if(win.ShowModal() == wxID_OK)
        {
            ConverterApplication.Assign(ConverterFiles[win.GetSelection()]);
        }
        else
        {
            ConverterFiles.Clear();
            ConverterLabels.Clear();
        }
    }

    if(ConverterFiles.GetCount() == 1)
    {
        ConverterApplication.Assign(ConverterFiles[0]);
    }

    if(ConverterFiles.GetCount() < 1)
    {
        ConverterApplication.SetName(wxT("ffmpeg")); // keep same extension as this application!
        wxTextEntryDialog win(NULL, wxT("No video converter has been found in the application or system directory.\nPlease enter a custom video converter:"), wxT("Enter Video Converter"));
        win.SetValue(ConverterApplication.GetFullPath());
        if(win.ShowModal() == wxID_OK)
        {
            ConverterApplication.Assign(win.GetValue());
        }
    }

    // initialize codec members

    AVCodec* pCodec = NULL;
    while((pCodec = av_codec_next(pCodec)))
    {
        CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_NONE;

        if(pCodec->type == AVMEDIA_TYPE_VIDEO)
        {
            if(pCodec->encode2)
            {
                VideoCodecList.Add(wxString::FromUTF8(pCodec->name));
            }
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_VIDEO;
        }
        if(pCodec->type == AVMEDIA_TYPE_AUDIO)
        {
            if(pCodec->encode2)
            {
                AudioCodecList.Add(wxString::FromUTF8(pCodec->name));
            }
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_AUDIO;
        }
        if(pCodec->type == AVMEDIA_TYPE_SUBTITLE)
        {
            if(pCodec->encode2)
            {
                SubtitleCodecList.Add(wxString::FromUTF8(pCodec->name));
            }
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_SUBTITLE;
        }
        if(pCodec->type == AVMEDIA_TYPE_ATTACHMENT)
        {
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_ATTACHMENT;
        }
        if(pCodec->type == AVMEDIA_TYPE_DATA)
        {
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_DATA;
        }
        if(pCodec->type == AVMEDIA_TYPE_NB)
        {
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_NB;
        }
        if(pCodec->type == AVMEDIA_TYPE_UNKNOWN)
        {
            CodecMediaMap[pCodec->id] = AVMEDIA_FLAG_UNKNOWN;
        }
    }
    pCodec = NULL;

    // initialize format related members

    wxString format;
    wxString extension;
    //CodecID SupportedCodec;
    //unsigned int IterateCodec; // CodecID enumerator used as unsigned int
    AVMediaFlags SupportedMedia;
    AVOutputFormat* pOutFormat = NULL;
    while((pOutFormat = av_oformat_next(pOutFormat)))
    {
        format = wxString::FromUTF8(pOutFormat->name);
        extension = wxString::FromUTF8(pOutFormat->extensions);
        SupportedMedia = AVMEDIA_FLAG_NONE;

        // if more then one extensions exist, use first available extension
        if(extension.Contains(wxT(",")))
        {
            extension = extension.BeforeFirst(',');
        }

        // if no extension exists, use format name as extension
        if(extension.IsEmpty())
        {
            extension = format;
        }

        // supported codec_tag detection is not working properly
        /*
        if(pOutFormat->codec_tag != NULL)
        {
            if(FormatMediaMap[format] == AVMEDIA_FLAG_NONE)
            {
                FormatMediaMap[format] = AVMEDIA_FLAG_NONE;
            }

            // iterate through each codec id and chech if this id is present in pOutFormat->codec_tag
            IterateCodec = 1; // 0 = CODEC_ID_NONE
            SupportedCodec = (CodecID)IterateCodec; // 0 = CODEC_ID_NONE
            while(SupportedCodec != CODEC_ID_NONE)
            {
                SupportedCodec = av_codec_get_id(pOutFormat->codec_tag, (CodecID)IterateCodec);
                FormatMediaMap[format] = (AVMediaFlags)(FormatMediaMap[format] | CodecMediaMap[SupportedCodec]);
                IterateCodec++;
            }
        }
        */

        // set format supported media flags and overwrite some extensions

        if(format.IsSameAs(wxT("3g2"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          3GP2 format
        if(format.IsSameAs(wxT("3gp"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          3GP format
        if(format.IsSameAs(wxT("RoQ"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            raw id RoQ format
        if(format.IsSameAs(wxT("a64"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            a64 - video for Commodore 64
        if(format.IsSameAs(wxT("ac3"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw AC-3
        if(format.IsSameAs(wxT("adts"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           ADTS AAC
        if(format.IsSameAs(wxT("adx"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           CRI ADX
        if(format.IsSameAs(wxT("aiff"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           Audio IFF
        if(format.IsSameAs(wxT("alaw"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM A-law format
        if(format.IsSameAs(wxT("alsa"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           ALSA audio output
        if(format.IsSameAs(wxT("amr"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           3GPP AMR file format
        if(format.IsSameAs(wxT("asf"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_ADVANCED; } //        ASF format
        if(format.IsSameAs(wxT("asf_stream"))){     /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_ADVANCED; } //        ASF format
        if(format.IsSameAs(wxT("ass"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_SUBTITLE; } //        Advanced SubStation Alpha subtitle format
        if(format.IsSameAs(wxT("au"))){             /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           SUN AU format
        if(format.IsSameAs(wxT("avi"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            AVI format
        if(format.IsSameAs(wxT("avm2"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_DATA; } //            Flash 9 (AVM2) format
        if(format.IsSameAs(wxT("cavsvideo"))){      /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          raw Chinese AVS video
        if(format.IsSameAs(wxT("crc"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_DATA; } //            CRC testing format
        if(format.IsSameAs(wxT("daud"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           D-Cinema audio format
        if(format.IsSameAs(wxT("dirac"))){          /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw Dirac
        if(format.IsSameAs(wxT("dnxhd"))){          /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw DNxHD (SMPTE VC-3)
        if(format.IsSameAs(wxT("dts"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw DTS
        if(format.IsSameAs(wxT("dv"))){             /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            DV video format
        if(format.IsSameAs(wxT("dvd"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          MPEG-2 PS format (DVD VOB)
        if(format.IsSameAs(wxT("eac3"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw E-AC-3
        if(format.IsSameAs(wxT("f32be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM 32 bit floating-point big-endian format
        if(format.IsSameAs(wxT("f32le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM 32 bit floating-point little-endian format
        if(format.IsSameAs(wxT("f64be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM 64 bit floating-point big-endian format
        if(format.IsSameAs(wxT("f64le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM 64 bit floating-point little-endian format
        if(format.IsSameAs(wxT("ffm"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            FFM (AVserver live feed) format
        if(format.IsSameAs(wxT("ffmetadata"))){     /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_DATA; } //            FFmpeg metadata in text format
        if(format.IsSameAs(wxT("filmstrip"))){      /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           Adobe Filmstrip
        if(format.IsSameAs(wxT("flac"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw FLAC
        if(format.IsSameAs(wxT("flv"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            FLV format
        if(format.IsSameAs(wxT("framecrc"))){       /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_DATA; } //            framecrc testing format
        if(format.IsSameAs(wxT("framemd5"))){       /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_DATA; } //            Per-frame MD5 testing format
        if(format.IsSameAs(wxT("g722"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw G.722
        if(format.IsSameAs(wxT("gif"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_IMG2SEQUENCE; } //    GIF Animation
        if(format.IsSameAs(wxT("gxf"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            GXF format
        if(format.IsSameAs(wxT("h261"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw H.261
        if(format.IsSameAs(wxT("h263"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw H.263
        if(format.IsSameAs(wxT("h264"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw H.264 video format
        if(format.IsSameAs(wxT("image2"))){         extension = wxT("png");     SupportedMedia = AVMEDIA_FLAG_IMG2SEQUENCE; } //    image2 sequence
        if(format.IsSameAs(wxT("image2pipe"))){     /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_IMG2SEQUENCE; } //    piped image2 sequence
        if(format.IsSameAs(wxT("ipod"))){           extension = wxT("mp4");     SupportedMedia = AVMEDIA_FLAG_COMMON; } //          iPod H.264 MP4 format
        if(format.IsSameAs(wxT("ivf"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            On2 IVF
        if(format.IsSameAs(wxT("latm"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           LOAS/LATM
        if(format.IsSameAs(wxT("m4v"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw MPEG-4 video format
        if(format.IsSameAs(wxT("matroska"))){       extension = wxT("mkv");     SupportedMedia = AVMEDIA_FLAG_COMPLETE; } //        Matroska file format
        if(format.IsSameAs(wxT("md5"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_DATA; } //            MD5 testing format
        if(format.IsSameAs(wxT("mjpeg"))){          /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw MJPEG video
        if(format.IsSameAs(wxT("mlp"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw MLP
        if(format.IsSameAs(wxT("mmf"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           Yamaha SMAF
        if(format.IsSameAs(wxT("mov"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMPLETE; } //        MOV format
        if(format.IsSameAs(wxT("mp2"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           MPEG audio layer 2
        if(format.IsSameAs(wxT("mp3"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           MPEG audio layer 3
        if(format.IsSameAs(wxT("mp4"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMPLETE; } //        MP4 format
        if(format.IsSameAs(wxT("mpeg"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            MPEG-1 System format
        if(format.IsSameAs(wxT("mpeg1video"))){     extension = wxT("m1v");     SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw MPEG-1 video
        if(format.IsSameAs(wxT("mpeg2video"))){     extension = wxT("m2v");     SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw MPEG-2 video
        if(format.IsSameAs(wxT("mpegts"))){         /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          MPEG-2 transport stream format
        if(format.IsSameAs(wxT("mpjpeg"))){         /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           MIME multipart JPEG format
        if(format.IsSameAs(wxT("mulaw"))){          /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM mu-law format
        if(format.IsSameAs(wxT("mxf"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            Material eXchange Format
        if(format.IsSameAs(wxT("mxf_d10"))){        /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            Material eXchange Format, D-10 Mapping
        if(format.IsSameAs(wxT("null"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw null video format
        if(format.IsSameAs(wxT("nut"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          NUT format
        if(format.IsSameAs(wxT("ogg"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          Ogg
        if(format.IsSameAs(wxT("oma"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           Sony OpenMG audio
        if(format.IsSameAs(wxT("oss"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           Open Sound System playback
        if(format.IsSameAs(wxT("psp"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          PSP MP4 format
        if(format.IsSameAs(wxT("rawvideo"))){       /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           raw video format
        if(format.IsSameAs(wxT("rcv"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           VC-1 test bitstream
        if(format.IsSameAs(wxT("rm"))){             /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          RealMedia format
        if(format.IsSameAs(wxT("rso"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           Lego Mindstorms RSO format
        if(format.IsSameAs(wxT("rtp"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            RTP output format
        if(format.IsSameAs(wxT("rtsp"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            RTSP output format
        if(format.IsSameAs(wxT("s16be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 16 bit big-endian format
        if(format.IsSameAs(wxT("s16le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 16 bit little-endian format
        if(format.IsSameAs(wxT("s24be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 24 bit big-endian format
        if(format.IsSameAs(wxT("s24le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 24 bit little-endian format
        if(format.IsSameAs(wxT("s32be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 32 bit big-endian format
        if(format.IsSameAs(wxT("s32le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 32 bit little-endian format
        if(format.IsSameAs(wxT("s8"))){             extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM signed 8 bit format
        if(format.IsSameAs(wxT("sap"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           SAP output format (Atari?)
        if(format.IsSameAs(wxT("segment"))){        /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            segment muxer
        if(format.IsSameAs(wxT("smjpeg"))){         /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_VIDEO; } //           Loki SDL MJPEG
        if(format.IsSameAs(wxT("sox"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           SoX native format
        if(format.IsSameAs(wxT("spdif"))){          /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           IEC 61937 (used on S/PDIF - IEC958)
        if(format.IsSameAs(wxT("srt"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_SUBTITLE; } //        SubRip subtitle format
        if(format.IsSameAs(wxT("svcd"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          MPEG-2 PS format (VOB)
        if(format.IsSameAs(wxT("swf"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            Flash format
        if(format.IsSameAs(wxT("truehd"))){         /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           raw TrueHD
        if(format.IsSameAs(wxT("u16be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 16 bit big-endian format
        if(format.IsSameAs(wxT("u16le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 16 bit little-endian format
        if(format.IsSameAs(wxT("u24be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 24 bit big-endian format
        if(format.IsSameAs(wxT("u24le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 24 bit little-endian format
        if(format.IsSameAs(wxT("u32be"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 32 bit big-endian format
        if(format.IsSameAs(wxT("u32le"))){          extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 32 bit little-endian format
        if(format.IsSameAs(wxT("u8"))){             extension = wxT("pcm");     SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           PCM unsigned 8 bit format
        if(format.IsSameAs(wxT("vcd"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            MPEG-1 System format (VCD)
        if(format.IsSameAs(wxT("vob"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_COMMON; } //          MPEG-2 PS format (VOB)
        if(format.IsSameAs(wxT("voc"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           Creative Voice file format
        if(format.IsSameAs(wxT("wav"))){            /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_AUDIO; } //           WAV format
        if(format.IsSameAs(wxT("webm"))){           /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            WebM file format
        if(format.IsSameAs(wxT("yuv4mpegpipe"))){   /*extension = wxT("");*/    SupportedMedia = AVMEDIA_FLAG_BASE; } //            YUV4MPEG pipe format

        FormatList.Add(format);
        FormatExtensionMap[format] = extension;
        FormatMediaMap[format] = SupportedMedia;

        // SupportedCodecs = NULL;
    }
    pOutFormat = NULL;

    // special case for multiple selections
    FormatMediaMap[wxT("*")] = AVMEDIA_FLAG_COMPLETE;

    // initialize pixel format members

    PixelDescriptionMap[AV_PIX_FMT_YUV420P] = wxT("8bit YUV420");
    PixelDescriptionMap[AV_PIX_FMT_YUYV422] = wxT("8bit YUYV422");
    PixelDescriptionMap[AV_PIX_FMT_RGB24] = wxT("8bit RGB24");
    PixelDescriptionMap[AV_PIX_FMT_BGR24] = wxT("8bit BGR24");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P] = wxT("8bit YUV422");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P] = wxT("8bit YUV444");
    PixelDescriptionMap[AV_PIX_FMT_YUV410P] = wxT("8bit YUV410");
    PixelDescriptionMap[AV_PIX_FMT_YUV411P] = wxT("8bit YUV411");
    PixelDescriptionMap[AV_PIX_FMT_GRAY8] = wxT("8bit GRAY8");
    PixelDescriptionMap[AV_PIX_FMT_MONOWHITE] = wxT("1bit MONOWHITE");
    PixelDescriptionMap[AV_PIX_FMT_MONOBLACK] = wxT("1bit MONOBLACK");
    PixelDescriptionMap[AV_PIX_FMT_PAL8] = wxT("8bit PAL8");
    PixelDescriptionMap[AV_PIX_FMT_YUVJ420P] = wxT("8bit YUVJ420");
    PixelDescriptionMap[AV_PIX_FMT_YUVJ422P] = wxT("8bit YUVJ422");
    PixelDescriptionMap[AV_PIX_FMT_YUVJ444P] = wxT("8bit YUVJ444");
    PixelDescriptionMap[AV_PIX_FMT_XVMC_MPEG2_MC] = wxT("XVMC-MC");
    PixelDescriptionMap[AV_PIX_FMT_XVMC_MPEG2_IDCT] = wxT("XVMC-IDCT");
    PixelDescriptionMap[AV_PIX_FMT_UYVY422] = wxT("8bit UYVY422");
    PixelDescriptionMap[AV_PIX_FMT_UYYVYY411] = wxT("8bit UYVY411");
    PixelDescriptionMap[AV_PIX_FMT_BGR8] = wxT("2.6bit BGR8");
    PixelDescriptionMap[AV_PIX_FMT_BGR4] = wxT("1.3bit BGR4");
    PixelDescriptionMap[AV_PIX_FMT_BGR4_BYTE] = wxT("2.6bit BGR4BYTE");
    PixelDescriptionMap[AV_PIX_FMT_RGB8] = wxT("2.6bit RGB8");
    PixelDescriptionMap[AV_PIX_FMT_RGB4] = wxT("1.3bit RGB4");
    PixelDescriptionMap[AV_PIX_FMT_RGB4_BYTE] = wxT("2.6bit RGB4BYTE");
    PixelDescriptionMap[AV_PIX_FMT_NV12] = wxT("8bit NV12420");
    PixelDescriptionMap[AV_PIX_FMT_NV21] = wxT("8bit NV21420");
    PixelDescriptionMap[AV_PIX_FMT_ARGB] = wxT("8bit ARGB");
    PixelDescriptionMap[AV_PIX_FMT_RGBA] = wxT("8bit RGBA");
    PixelDescriptionMap[AV_PIX_FMT_ABGR] = wxT("8bit ABGR");
    PixelDescriptionMap[AV_PIX_FMT_BGRA] = wxT("8bit BGRA");
    PixelDescriptionMap[AV_PIX_FMT_GRAY16BE] = wxT("16bit GRAY16BE");
    PixelDescriptionMap[AV_PIX_FMT_GRAY16LE] = wxT("16bit GRAY16LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV440P] = wxT("8bit YUV440");
    PixelDescriptionMap[AV_PIX_FMT_YUVJ440P] = wxT("8bit YUVJ440");
    PixelDescriptionMap[AV_PIX_FMT_YUVA420P] = wxT("8bit YUVA420");
    PixelDescriptionMap[AV_PIX_FMT_VDPAU_H264] = wxT("VDPAU-H264");
    PixelDescriptionMap[AV_PIX_FMT_VDPAU_MPEG1] = wxT("VDPAU-MPEG1");
    PixelDescriptionMap[AV_PIX_FMT_VDPAU_MPEG2] = wxT("VDPAU-MPEG2");
    PixelDescriptionMap[AV_PIX_FMT_VDPAU_WMV3] = wxT("VDPAU-WMV3");
    PixelDescriptionMap[AV_PIX_FMT_VDPAU_VC1] = wxT("VDPAU-VC1");
    PixelDescriptionMap[AV_PIX_FMT_RGB48BE] = wxT("16bit RGB48BE");
    PixelDescriptionMap[AV_PIX_FMT_RGB48LE] = wxT("16bit RGB48LE");
    PixelDescriptionMap[AV_PIX_FMT_RGB565BE] = wxT("5.3bit RGB565BE");
    PixelDescriptionMap[AV_PIX_FMT_RGB565LE] = wxT("5.3bit RGB565LE");
    PixelDescriptionMap[AV_PIX_FMT_RGB555BE] = wxT("5.3bit RGB555BE");
    PixelDescriptionMap[AV_PIX_FMT_RGB555LE] = wxT("5.3bit RGB555LE");
    PixelDescriptionMap[AV_PIX_FMT_BGR565BE] = wxT("5.3bit BGR565BE");
    PixelDescriptionMap[AV_PIX_FMT_BGR565LE] = wxT("5.3bit BGR565LE");
    PixelDescriptionMap[AV_PIX_FMT_BGR555BE] = wxT("5.3bit BGR555BE");
    PixelDescriptionMap[AV_PIX_FMT_BGR555LE] = wxT("5.3bit BGR555LE");
    PixelDescriptionMap[AV_PIX_FMT_VAAPI_MOCO] = wxT("VAAPI-MOCO");
    PixelDescriptionMap[AV_PIX_FMT_VAAPI_IDCT] = wxT("AAPI-IDCT");
    PixelDescriptionMap[AV_PIX_FMT_VAAPI_VLD] = wxT("VAAPI-VLD");
    PixelDescriptionMap[AV_PIX_FMT_YUV420P16LE] = wxT("16bit YUV420LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV420P16BE] = wxT("16bit YUV420BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P16LE] = wxT("16bit YUV422LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P16BE] = wxT("16bit YUV422BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P16LE] = wxT("16bit YUV444LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P16BE] = wxT("16bit YUV444BE");
    PixelDescriptionMap[AV_PIX_FMT_VDPAU_MPEG4] = wxT("VDPAU-MPEG4");
    PixelDescriptionMap[AV_PIX_FMT_DXVA2_VLD] = wxT("DXVA2-VLD");
    PixelDescriptionMap[AV_PIX_FMT_RGB444LE] = wxT("5.3bit RGB444LE");
    PixelDescriptionMap[AV_PIX_FMT_RGB444BE] = wxT("5.3bit RGB444BE");
    PixelDescriptionMap[AV_PIX_FMT_BGR444LE] = wxT("5.3bit BGR444LE");
    PixelDescriptionMap[AV_PIX_FMT_BGR444BE] = wxT("5.3bit BGR444BE");
    PixelDescriptionMap[AV_PIX_FMT_Y400A] = wxT("8bit Y400A");
    PixelDescriptionMap[AV_PIX_FMT_BGR48BE] = wxT("16bit BGR48BE");
    PixelDescriptionMap[AV_PIX_FMT_BGR48LE] = wxT("16bit BGR48LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV420P9BE] = wxT("9bit YUV420BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV420P9LE] = wxT("9bit YUV420LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV420P10BE] = wxT("10bit YUV420BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV420P10LE] = wxT("10bit YUV420LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P10BE] = wxT("10bit YUV422BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P10LE] = wxT("10bit YUV422LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P9BE] = wxT("9bit YUV444BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P9LE] = wxT("9bit YUV444LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P10BE] = wxT("10bit YUV444BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV444P10LE] = wxT("10bit YUV444LE");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P9BE] = wxT("9bit YUV422BE");
    PixelDescriptionMap[AV_PIX_FMT_YUV422P9LE] = wxT("9bit YUV422LE");
    PixelDescriptionMap[AV_PIX_FMT_VDA_VLD] = wxT("?bit VDA VLD");
    PixelDescriptionMap[AV_PIX_FMT_GBRP] = wxT("8bit GBR444");
    PixelDescriptionMap[AV_PIX_FMT_GBRP9BE] = wxT("9bit GBR444BE");
    PixelDescriptionMap[AV_PIX_FMT_GBRP9LE] = wxT("9bit GBR444LE");
    PixelDescriptionMap[AV_PIX_FMT_GBRP10BE] = wxT("10bit GBR444BE");
    PixelDescriptionMap[AV_PIX_FMT_GBRP10LE] = wxT("10bit GBR444LE");
    PixelDescriptionMap[AV_PIX_FMT_GBRP16BE] = wxT("16bit GBR444BE");
    PixelDescriptionMap[AV_PIX_FMT_GBRP16LE] = wxT("16bit GBR444LE");
}

wxString Libav::MilliToSMPTE(int64_t MilliSeconds)
{
    int hh = MilliSeconds/(60*60*1000);
    MilliSeconds = MilliSeconds%(60*60*1000);
    int mm = MilliSeconds/(60*1000);
    MilliSeconds = MilliSeconds%(60*1000);
    int ss = MilliSeconds/1000;
    int ms = MilliSeconds%1000;

    return wxString::Format(wxT("%02i:%02i:%02i.%03i"), hh, mm, ss, ms);
}

wxString Libav::MilliToSeconds(int64_t MilliSeconds)
{
    int ss = MilliSeconds/1000;
    int ms = MilliSeconds%1000;

    if(ms > 0)
    {
        return wxString::Format(wxT("%i.%i"), ss, ms);
    }
    return wxString::Format(wxT("%i"), ss);
}

wxArrayString Libav::FormatVideoCodecs(wxString ContainerFormat)
{
    wxArrayString codecs;

    codecs.Add(wxT("default"));
    codecs.Add(wxT("copy"));

    if(ContainerFormat.IsSameAs(wxT("matroska")))
    {
        codecs.Add(wxT("libx265"));
        codecs.Add(wxT("libx264"));
        codecs.Add(wxT("libxvid"));
        codecs.Add(wxT("libvpx"));
        codecs.Add(wxT("libvpx-vp9"));
        codecs.Add(wxT("mpeg4"));
        codecs.Add(wxT("mpeg1video"));
        codecs.Add(wxT("mpeg2video"));
    }

    if(ContainerFormat.IsSameAs(wxT("mp4")))
    {
        codecs.Add(wxT("libx265"));
        codecs.Add(wxT("libx264"));
        codecs.Add(wxT("libxvid"));
        codecs.Add(wxT("libvpx"));
        codecs.Add(wxT("libvpx-vp9"));
        codecs.Add(wxT("mpeg4"));
        codecs.Add(wxT("mpeg1video"));
        codecs.Add(wxT("mpeg2video"));
    }

    if(ContainerFormat.IsSameAs(wxT("mov")))
    {
        codecs.Add(wxT("libx265"));
        codecs.Add(wxT("libx264"));
        codecs.Add(wxT("libxvid"));
        codecs.Add(wxT("libvpx"));
        codecs.Add(wxT("libvpx-vp9"));
        codecs.Add(wxT("mpeg4"));
        codecs.Add(wxT("mpeg1video"));
        codecs.Add(wxT("mpeg2video"));
    }

    if(ContainerFormat.IsSameAs(wxT("ogg")))
    {
        codecs.Add(wxT("libtheora"));
    }

    if(ContainerFormat.IsSameAs(wxT("webm")))
    {
        codecs.Add(wxT("libvpx"));
        codecs.Add(wxT("libvpx-vp9"));
    }

    if(ContainerFormat.IsSameAs(wxT("mpeg")))
    {
        codecs.Add(wxT("mpeg1video"));
        codecs.Add(wxT("mpeg2video"));
    }

    if(ContainerFormat.IsSameAs(wxT("avi")))
    {
        codecs.Add(wxT("libxvid"));
    }

    return codecs;
}

wxArrayString Libav::FormatAudioCodecs(wxString ContainerFormat)
{
    wxArrayString codecs;

    codecs.Add(wxT("default"));
    codecs.Add(wxT("copy"));

    if(ContainerFormat.IsSameAs(wxT("matroska")))
    {
        codecs.Add(wxT("libfdk_aac"));
        codecs.Add(wxT("libfaac"));
        codecs.Add(wxT("aac"));
        codecs.Add(wxT("ac3"));
        codecs.Add(wxT("flac"));
        codecs.Add(wxT("mp2"));
        codecs.Add(wxT("libvorbis"));
        codecs.Add(wxT("libmp3lame"));
        codecs.Add(wxT("adpcm_ima_wav"));
    }

    if(ContainerFormat.IsSameAs(wxT("mp4")))
    {
        codecs.Add(wxT("libfdk_aac"));
        codecs.Add(wxT("libfaac"));
        codecs.Add(wxT("aac"));
        codecs.Add(wxT("ac3"));
        codecs.Add(wxT("flac"));
        codecs.Add(wxT("mp2"));
        codecs.Add(wxT("libvorbis"));
        codecs.Add(wxT("libmp3lame"));
        codecs.Add(wxT("adpcm_ima_wav"));
    }

    if(ContainerFormat.IsSameAs(wxT("mov")))
    {
        codecs.Add(wxT("libfdk_aac"));
        codecs.Add(wxT("libfaac"));
        codecs.Add(wxT("aac"));
        codecs.Add(wxT("ac3"));
        codecs.Add(wxT("flac"));
        codecs.Add(wxT("mp2"));
        codecs.Add(wxT("libvorbis"));
        codecs.Add(wxT("libmp3lame"));
        codecs.Add(wxT("adpcm_ima_wav"));
    }

    if(ContainerFormat.IsSameAs(wxT("ogg")))
    {
        codecs.Add(wxT("flac"));
        codecs.Add(wxT("libvorbis"));
    }

    if(ContainerFormat.IsSameAs(wxT("webm")))
    {
        codecs.Add(wxT("libvorbis"));
    }

    if(ContainerFormat.IsSameAs(wxT("mpeg")))
    {
        codecs.Add(wxT("mp2"));
        codecs.Add(wxT("libmp3lame"));
    }

    if(ContainerFormat.IsSameAs(wxT("mp3")))
    {
        codecs.Add(wxT("libmp3lame"));
    }

    if(ContainerFormat.IsSameAs(wxT("ac3")))
    {
        codecs.Add(wxT("ac3"));
    }

    if(ContainerFormat.IsSameAs(wxT("flac")))
    {
        codecs.Add(wxT("flac"));
    }

    if(ContainerFormat.IsSameAs(wxT("wav")))
    {
        codecs.Add(wxT("adpcm_ima_wav"));
    }

    return codecs;
}

wxArrayString Libav::FormatSubtitleCodecs(wxString ContainerFormat)
{
    wxArrayString codecs;

    codecs.Add(wxT("default"));
    codecs.Add(wxT("copy"));

    if(ContainerFormat.IsSameAs(wxT("matroska")))
    {
        codecs.Add(wxT("ass"));
        codecs.Add(wxT("srt"));
    }

    if(ContainerFormat.IsSameAs(wxT("mp4")))
    {

    }

    if(ContainerFormat.IsSameAs(wxT("mov")))
    {

    }

    if(ContainerFormat.IsSameAs(wxT("ogg")))
    {

    }

    if(ContainerFormat.IsSameAs(wxT("webm")))
    {

    }

    if(ContainerFormat.IsSameAs(wxT("mpeg")))
    {

    }

    if(ContainerFormat.IsSameAs(wxT("ass")))
    {
        codecs.Add(wxT("ass"));
    }

    if(ContainerFormat.IsSameAs(wxT("srt")))
    {
        codecs.Add(wxT("srt"));
    }

    return codecs;
}

wxString Libav::GetPicType(AVPictureType PicType)
{
    switch(PicType)
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

GLint Libav::GetGLFormat(AVPixelFormat PixFormat)
{
    switch(PixFormat)
    {
        // currently limited to gl_formats of gl_type GL_UNSIGNED_BYTE
        //case : return GL_RED;
        //case : return GL_RG;
        case AV_PIX_FMT_RGB24: return GL_RGB;
        case AV_PIX_FMT_BGR24: return GL_BGR;
        case AV_PIX_FMT_RGB32: return GL_RGBA;
        case AV_PIX_FMT_BGR32: return GL_BGRA;
        default: return 0;
    }
}
