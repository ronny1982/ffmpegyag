#include "EncodingFileLoader.h"

static int CompareIndexEntry(IndexEntry** First, IndexEntry** Second)
{
    return (int)((*First)->Timestamp - (*Second)->Timestamp);
}

EncodingFileLoader::EncodingFileLoader(wxFileName InputFile)
{
    File = InputFile;

    pFormatCtx = NULL;

    VideoStreams.Clear();
    AudioStreams.Clear();
    SubtitleStreams.Clear();

    if(File.FileExists())
    {
        FileSize = (int64_t)(wxFile(File.GetFullPath()).Length());

        av_register_all();
        //avcodec_register_all();

        if(avformat_open_input(&pFormatCtx, File.GetFullPath().ToUTF8().data(), NULL, NULL) == 0)
        {
            //pFormatCtx->flags |= 0x0040; //AVFMT_FLAG_NOBUFFER;
            if(avformat_find_stream_info(pFormatCtx, NULL) > -1)
            {
                FileDuration = (int64_t)1000 * (int64_t)pFormatCtx->duration / (int64_t)AV_TIME_BASE;

                // set progressbar maximum to duration in seconds (at least 1 so maximum is > 0 to prevent instant closing of dialog)
                int progress_max = wxMax(1, (int)((int64_t)pFormatCtx->duration/(int64_t)AV_TIME_BASE));
                wxProgressDialog* ProgressDialog = new wxProgressDialog(wxT("Building Index..."), File.GetFullPath(), progress_max, NULL, wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT);

                AVStream* stream;

                // +++++++++++++++++++++++++++++
                // +++ INIT STREAMS & CODECS +++
                // +++++++++++++++++++++++++++++
                //{
                    AVCodecContext* pCodecCtx;
                    int64_t StreamSize[pFormatCtx->nb_streams];

                    for(unsigned int i=0; i<pFormatCtx->nb_streams; i++)
                    {
                        stream = pFormatCtx->streams[i];
                        StreamSize[i] = 0;

                        // initialize codec context for each stream (if not done, decoding packets will crash!)
                        pCodecCtx = stream->codec;

                        if(pCodecCtx->codec_type == AVMEDIA_TYPE_VIDEO)
                        {
                            avcodec_open2(pCodecCtx, avcodec_find_decoder(pCodecCtx->codec_id), NULL);
                            VideoStreams.Add(new VideoStream(i, false));
                            VideoStreams[VideoStreams.GetCount()-1]->IndexEntries.Alloc(GetStreamEstimatedFrameCount(i)+10); // add 10 security frames
                        }

                        if(pCodecCtx->codec_type == AVMEDIA_TYPE_AUDIO)
                        {
                            avcodec_open2(pCodecCtx, avcodec_find_decoder(pCodecCtx->codec_id), NULL);
                            AudioStreams.Add(new AudioStream(i, false));
                        }

                        if(pCodecCtx->codec_type == AVMEDIA_TYPE_SUBTITLE)
                        {
                            avcodec_open2(pCodecCtx, avcodec_find_decoder(pCodecCtx->codec_id), NULL);
                            SubtitleStreams.Add(new SubtitleStream(i, false));
                        }
                    }

                    pCodecCtx = NULL;
                //}

                // +++++++++++++++++++
                // +++ BUILD INDEX +++
                // +++++++++++++++++++
                //{
                    AVPacket packet;
                    size_t vpkt_count = 0;
                    while(!av_read_frame(pFormatCtx, &packet))
                    {
                        stream = pFormatCtx->streams[packet.stream_index];
                        StreamSize[packet.stream_index] += packet.size;

                        // only process video packets
                        if(stream->codec->codec_type == AVMEDIA_TYPE_VIDEO/* || (stream->codec->codec_type & AVMEDIA_TYPE_AUDIO) || (stream->codec->codec_type & AVMEDIA_TYPE_SUBTITLE)*/)
                        {
                            if(packet.pts == (int64_t)AV_NOPTS_VALUE)
                            {
                                packet.pts = packet.dts;
                            }

                            if(vpkt_count%100 == 0)
                            {
                                // set progressbar to packet time in seconds
                                if(!ProgressDialog->Update((int)(((int64_t)packet.pts - (int64_t)stream->start_time) * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den)))
                                {
                                    break;
                                }
                            }

                            // add this packet to the corresponding video stream
                            for(size_t i=0; i<VideoStreams.GetCount(); i++)
                            {
                                if(packet.stream_index == (int)VideoStreams[i]->ID)
                                {
                                    VideoStreams[i]->IndexEntries.Add(new IndexEntry(packet.pts, packet.pos, (packet.flags == AV_PKT_FLAG_KEY)));
                                    break;
                                }
                            }

                            vpkt_count++;
                        }
                        av_free_packet(&packet);
                    }

                    // sort timestamps for each video stream because of b-frame prediction ordered frames (dts)
                    for(size_t v=0; v<VideoStreams.GetCount(); v++)
                    {
                        VideoStreams[v]->IndexEntries.Sort(CompareIndexEntry);
                    }
                //}

                AVDictionaryEntry* MetaInfo;

                // ++++++++++++++++++++++++++++++
                // +++ SET VIDEO STREAM INFOS +++
                // ++++++++++++++++++++++++++++++
                //{
                    VideoStream* vStream;
                    for(size_t v=0; v<VideoStreams.GetCount(); v++)
                    {
                        stream = pFormatCtx->streams[VideoStreams[v]->ID];
                        vStream = VideoStreams[v];

                        vStream->Size = StreamSize[VideoStreams[v]->ID];
                        vStream->FrameCount = vStream->IndexEntries.GetCount(); // pFormatCtx->streams[i]->nb_frames;

                        if(vStream->FrameCount > 0)
                        {
                            vStream->StartTime = (int64_t)1000 * vStream->IndexEntries[0]->Timestamp * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        else
                        {
                            vStream->StartTime = stream->start_time;
                        }
                        if(vStream->FrameCount > 0)
                        {
                            // length of last frame is considered
                            vStream->Duration = (int64_t)1000 * (vStream->IndexEntries[vStream->FrameCount-1]->Timestamp - vStream->IndexEntries[0]->Timestamp) * (int64_t)stream->time_base.num * ((int64_t)vStream->IndexEntries.GetCount()+1) / ((int64_t)stream->time_base.den * (int64_t)vStream->IndexEntries.GetCount());
                        }
                        else if(stream->duration > 0)
                        {
                            vStream->Duration = (int64_t)1000 * stream->duration * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        else
                        {
                            // use format duration
                            vStream->Duration = (int64_t)1000 * pFormatCtx->duration / AV_TIME_BASE;
                        }
                        if(stream->codec->bit_rate > 0)
                        {
                            vStream->Bitrate = stream->codec->bit_rate;
                        }
                        else if(vStream->Duration)
                        {
                            vStream->Bitrate = (int)(8 * vStream->Size * 1000 / vStream->Duration);
                        }
                        MetaInfo = av_dict_get(stream->metadata, "title", NULL, 0);
                        if(MetaInfo && MetaInfo->value)
                        {
                            vStream->Title = wxString::FromUTF8(MetaInfo->value);
                        }
                        else
                        {
                            vStream->Title = wxEmptyString;
                        }
                        MetaInfo = av_dict_get(stream->metadata, "language", NULL, 0);
                        if(MetaInfo && MetaInfo->value)
                        {
                            vStream->Language = wxString::FromUTF8(MetaInfo->value);
                        }
                        else
                        {
                            vStream->Language = wxEmptyString;
                        }
                        if(stream->codec->codec && stream->codec->codec->name)
                        {
                            vStream->CodecName = wxString::FromUTF8(stream->codec->codec->name);
                        }
                        else
                        {
                            vStream->CodecName = wxEmptyString;
                        }
                        if(stream->avg_frame_rate.den > 0)
                        {
                            vStream->FrameRate = av_q2d(stream->avg_frame_rate);
                        }
                        else if(stream->r_frame_rate.den > 0)
                        {
                            vStream->FrameRate = av_q2d(stream->r_frame_rate);
                        }
                        else
                        {
                            vStream->FrameRate = av_q2d((AVRational){vStream->FrameCount*1000, (int)vStream->Duration});
                        }
                        vStream->Width = stream->codec->width;
                        vStream->Height = stream->codec->height;
                        vStream->Profile = Libav::PixelDescriptionMap[stream->codec->pix_fmt] + wxString::Format(wxT(" @L%i"), stream->codec->level);

                        vStream = NULL;
                    }
                //}

                // ++++++++++++++++++++++++++++++
                // +++ SET AUDIO STREAM INFOS +++
                // ++++++++++++++++++++++++++++++
                //{
                    AudioStream* aStream;
                    for(size_t a=0; a<AudioStreams.GetCount(); a++)
                    {
                        stream = pFormatCtx->streams[AudioStreams[a]->ID];
                        aStream = AudioStreams[a];

                        aStream->Size = StreamSize[AudioStreams[a]->ID];

                        if(stream->nb_index_entries > 0)
                        {
                            aStream->StartTime = (int64_t)1000 * stream->index_entries[0].timestamp * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        else
                        {
                            aStream->StartTime = stream->start_time;
                        }
                        if(stream->duration > 0)
                        {
                            aStream->Duration = (int64_t)1000 * stream->duration * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        else if(stream->nb_index_entries > 0)
                        {
                            // NOTE: length of last frame is not considered
                            aStream->Duration = (int64_t)1000 * (stream->index_entries[stream->nb_index_entries-1].timestamp - stream->index_entries[0].timestamp) * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        if(stream->codec->bit_rate > 0)
                        {
                            aStream->Bitrate = stream->codec->bit_rate;
                        }
                        else if(aStream->Duration > 0)
                        {
                            aStream->Bitrate = (int)(8 * aStream->Size * 1000 / aStream->Duration);
                        }
                        MetaInfo = av_dict_get(stream->metadata, "title", NULL, 0);
                        if(MetaInfo && MetaInfo->value)
                        {
                            aStream->Title = wxString::FromUTF8(MetaInfo->value);
                        }
                        else
                        {
                            aStream->Title = wxEmptyString;
                        }
                        MetaInfo = av_dict_get(stream->metadata, "language", NULL, 0);
                        if(MetaInfo && MetaInfo->value)
                        {
                            aStream->Language = wxString::FromUTF8(MetaInfo->value);
                        }
                        else
                        {
                            aStream->Language = wxEmptyString;
                        }
                        if(stream->codec->codec && stream->codec->codec->name)
                        {
                            aStream->CodecName = wxString::FromUTF8(stream->codec->codec->name);
                        }
                        else
                        {
                            aStream->CodecName = wxEmptyString;
                        }
                        aStream->SampleRate = stream->codec->sample_rate;
                        aStream->ChannelCount = stream->codec->channels;

                        aStream = NULL;
                    }
                //}

                // +++++++++++++++++++++++++++++++++
                // +++ SET SUBTITLE STREAM INFOS +++
                // +++++++++++++++++++++++++++++++++
                //{
                    SubtitleStream* sStream;
                    for(size_t s=0; s<SubtitleStreams.GetCount(); s++)
                    {
                        stream = pFormatCtx->streams[SubtitleStreams[s]->ID];
                        sStream = SubtitleStreams[s];

                        sStream->Size = StreamSize[SubtitleStreams[s]->ID];

                        if(stream->nb_index_entries > 0)
                        {
                            sStream->StartTime = (int64_t)1000 * stream->index_entries[0].timestamp * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        else
                        {
                            sStream->StartTime = stream->start_time;
                        }
                        if(stream->duration > 0)
                        {
                            sStream->Duration = (int64_t)1000 * stream->duration * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        else if(stream->nb_index_entries > 0)
                        {
                            // NOTE: length of last frame is not considered
                            sStream->Duration = (int64_t)1000 * (stream->index_entries[stream->nb_index_entries-1].timestamp - stream->index_entries[0].timestamp) * (int64_t)stream->time_base.num / (int64_t)stream->time_base.den;
                        }
                        if(stream->codec->bit_rate > 0)
                        {
                            sStream->Bitrate = stream->codec->bit_rate;
                        }
                        else if(sStream->Duration > 0)
                        {
                            sStream->Bitrate = (int)(8 * sStream->Size * 1000 / sStream->Duration);
                        }
                        MetaInfo = av_dict_get(stream->metadata, "title", NULL, 0);
                        if(MetaInfo && MetaInfo->value)
                        {
                            sStream->Title = wxString::FromUTF8(MetaInfo->value);
                        }
                        else
                        {
                            sStream->Title = wxEmptyString;
                        }
                        MetaInfo = av_dict_get(stream->metadata, "language", NULL, 0);
                        if(MetaInfo && MetaInfo->value)
                        {
                            sStream->Language = wxString::FromUTF8(MetaInfo->value);
                        }
                        else
                        {
                            sStream->Language = wxEmptyString;
                        }
                        if(stream->codec->codec && stream->codec->codec->name)
                        {
                            sStream->CodecName = wxString::FromUTF8(stream->codec->codec->name);
                        }
                        else
                        {
                            sStream->CodecName = wxEmptyString;
                        }

                        sStream = NULL;
                    }
                //}

                MetaInfo = NULL;

                stream = NULL;

                ProgressDialog->Close();
                wxDELETE(ProgressDialog);
            }
        }
    }
}

EncodingFileLoader::~EncodingFileLoader()
{
    FlushBuffer();
    WX_CLEAR_ARRAY(VideoStreams);
    WX_CLEAR_ARRAY(AudioStreams);
    WX_CLEAR_ARRAY(SubtitleStreams);

    // close the video file
    if(pFormatCtx != NULL)
    {
        for(unsigned int i=0; i<pFormatCtx->nb_streams; i++)
        {
            avcodec_close(pFormatCtx->streams[i]->codec);
        }
        avformat_close_input(&pFormatCtx);
        av_free(pFormatCtx);
        pFormatCtx = NULL;
    }
}

int64_t EncodingFileLoader::GetStreamEstimatedFrameCount(unsigned int StreamIndex)
{
    if(pFormatCtx)
    {
        AVStream* stream = pFormatCtx->streams[StreamIndex];

        if(stream->nb_frames > 0)
        {
            // use existing frame count
            return stream->nb_frames;
        }
        else
        {
            // calculate estimated frame count

            int64_t EstimationDuration;
            AVRational EstimationTimeBase = stream->time_base;
            AVRational EstimationFrameRate = stream->avg_frame_rate;

            if(stream ->duration != (int64_t)AV_NOPTS_VALUE)
            {
                EstimationDuration = stream->duration;
            }
            else
            {
                // convert from base duration to stream time_base duration
                EstimationDuration = (pFormatCtx->duration * EstimationTimeBase.den) / (AV_TIME_BASE * EstimationTimeBase.num);
            }

            if(stream->codec->codec_type == AVMEDIA_TYPE_VIDEO || stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                if(stream->avg_frame_rate.den > 0)
                {
                    EstimationFrameRate = stream->avg_frame_rate;
                }
                else
                {
                    EstimationFrameRate = stream->r_frame_rate;
                }
            }

            if(stream->codec->codec_type & AVMEDIA_TYPE_SUBTITLE)
            {
                // assuming 0.5 subtitles / second
                EstimationFrameRate.num = 1;
                EstimationFrameRate.den = 2;
            }

            return (int64_t)(((int64_t)EstimationDuration * (int64_t)EstimationTimeBase.num * (int64_t)EstimationFrameRate.num ) / ((int64_t)EstimationTimeBase.den * (int64_t)EstimationFrameRate.den));
        }
    }
    return (int64_t)0;
}

bool EncodingFileLoader::CanRead()
{
    if(pFormatCtx != NULL)
    {
        return true;
    }
    return false;
}

void EncodingFileLoader::FlushBuffer()
{
    GOPBuffer.Flush();
    if(pFormatCtx != NULL)
    {
        for(unsigned int i=0; i<pFormatCtx->nb_streams; i++)
        {
            if(pFormatCtx->streams[i]->codec->codec)
            {
                avcodec_flush_buffers(pFormatCtx->streams[i]->codec);
            }
        }
    }
}

long EncodingFileLoader::SeekKeyFrameIndex(long VideoStreamIndex, long FrameIndex)
{
    // do not use av_index_search, because the used stream->index_entries might be empty (native search -> slow and corrupted)
    //return av_index_search_timestamp(pFormatCtx->streams[VideoStreams[VideoStreamIndex]->ID], VideoStreams[VideoStreamIndex]->IndexEntries[FrameIndex]->Timestamp, AVSEEK_FLAG_BACKWARD);

    if(FrameIndex >= (long)VideoStreams[VideoStreamIndex]->IndexEntries.GetCount())
    {
        FrameIndex = VideoStreams[VideoStreamIndex]->IndexEntries.GetCount()-1;
    }

    while(FrameIndex > 0 && !VideoStreams[VideoStreamIndex]->IndexEntries[FrameIndex]->Keyframe)
    {
        FrameIndex--;
    }

    return FrameIndex;
}

bool EncodingFileLoader::SetStreamPosition(long VideoStreamIndex, long KeyFrameIndex)
{
    unsigned int StreamID = VideoStreams[VideoStreamIndex]->ID;
    IndexEntry* info = VideoStreams[VideoStreamIndex]->IndexEntries[KeyFrameIndex];

    // use index based search, if index is available or byte position of frame unavailable
    if(pFormatCtx->streams[StreamID]->nb_index_entries > 0 || info->Position < 0)
    {
        if(av_seek_frame(pFormatCtx, StreamID, info->Timestamp, AVSEEK_FLAG_BACKWARD) > -1)
        {
            return true;
        }
    }
    else
    {
        // FIXME: byte positions sometimes wrong -> av_read_frame failed (i.e. Bakemonogatari.mkv)
        // works fine in thor.m2ts
        if(av_seek_frame(pFormatCtx, StreamID, info->Position, AVSEEK_FLAG_BYTE) > -1)
        {
            return true;
        }
        /*
        if(avio_seek(pFormatCtx->pb, info->Position, SEEK_SET) > -1)
        {
            return true;
        }
        */
    }

    return false;
}

int64_t EncodingFileLoader::GetTimeFromFrame(long VideoStreamIndex, long FrameIndex)
{
    if(pFormatCtx && VideoStreamIndex < (long)VideoStreams.GetCount())
    {
        if(FrameIndex < (long)VideoStreams[VideoStreamIndex]->IndexEntries.GetCount())
        {
            GetTimeFromTimestamp(VideoStreamIndex, VideoStreams[VideoStreamIndex]->IndexEntries[FrameIndex]->Timestamp);
        }
        else
        {
            return VideoStreams[VideoStreamIndex]->Duration;
        }
    }
    return (int64_t)0;
}

long EncodingFileLoader::GetFrameFromTimestamp(long VideoStreamIndex, int64_t Timestamp)
{
    long result = 0;

    size_t StartIndex = 0;
    size_t DivideIndex= 0;
    size_t EndIndex = 0;

    if(pFormatCtx && VideoStreamIndex < (long)VideoStreams.GetCount())
    {
        if(VideoStreams[VideoStreamIndex]->IndexEntries.GetCount() > 0)
        {
            StartIndex = 0;
            EndIndex = VideoStreams[VideoStreamIndex]->IndexEntries.GetCount() - 1;

            // divide & conquer until partition can not divided anymore
            while(StartIndex+1 < EndIndex)
            {
                DivideIndex = (StartIndex + EndIndex) / 2;
                if(Timestamp < VideoStreams[VideoStreamIndex]->IndexEntries[DivideIndex]->Timestamp)
                {
                    EndIndex = DivideIndex;
                }
                else
                {
                    StartIndex = DivideIndex;
                }
            }

            // return index of closest timestamp (works even if requested timestamp lies outside of interval)
            if(Timestamp - VideoStreams[VideoStreamIndex]->IndexEntries[StartIndex]->Timestamp < VideoStreams[VideoStreamIndex]->IndexEntries[EndIndex]->Timestamp - Timestamp )
            {
                result = (long)StartIndex;
            }
            else
            {
                result = (long)EndIndex;
            }
        }
    }
    return result;
}

long EncodingFileLoader::GetFrameFromTime(long VideoStreamIndex, int64_t Time)
{
    int64_t timestamp = GetTimestampFromTime(VideoStreamIndex, Time);
    return GetFrameFromTimestamp(VideoStreamIndex, timestamp);
}

int64_t EncodingFileLoader::GetTimeFromTimestamp(long VideoStreamIndex, int64_t Timestamp)
{
    if(pFormatCtx && VideoStreamIndex < (long)VideoStreams.GetCount())
    {
        return (int64_t)1000 * (Timestamp - VideoStreams[VideoStreamIndex]->IndexEntries[0]->Timestamp) * (int64_t)pFormatCtx->streams[VideoStreams[VideoStreamIndex]->ID]->time_base.num / (int64_t)pFormatCtx->streams[VideoStreams[VideoStreamIndex]->ID]->time_base.den;
    }
    return (int64_t)0;
}

int64_t EncodingFileLoader::GetTimestampFromTime(long VideoStreamIndex, int64_t Time)
{
    if(pFormatCtx && VideoStreamIndex < (long)VideoStreams.GetCount())
    {
        return Time * (int64_t)pFormatCtx->streams[VideoStreams[VideoStreamIndex]->ID]->time_base.den / (int64_t)pFormatCtx->streams[VideoStreams[VideoStreamIndex]->ID]->time_base.num / 1000 + VideoStreams[VideoStreamIndex]->IndexEntries[0]->Timestamp;
    }
    return (int64_t)0;
}

VideoFrame* EncodingFileLoader::GetVideoFrameData(long VideoStreamIndex, long FrameIndex, int TargetWidth, int TargetHeight, PixelFormat TargetPixelFormat)
{
    // TODO: search for minor memory leak

    // to improve performance there is no additional securitycheck for pFormatCtx, VideoStreamIndex & FrameIndex

    int StreamID = VideoStreams[VideoStreamIndex]->ID;
    AVCodecContext* pCodecCtx = pFormatCtx->streams[StreamID]->codec;

    int64_t Timestamp;
    if(FrameIndex < (long)VideoStreams[VideoStreamIndex]->IndexEntries.GetCount())
    {
        Timestamp = VideoStreams[VideoStreamIndex]->IndexEntries[FrameIndex]->Timestamp;
    }
    else
    {
        Timestamp = GetTimestampFromTime(VideoStreamIndex, VideoStreams[VideoStreamIndex]->Duration) + 1; // +1 to prevent rounding errors of integer timestamps (1,2,3,4,...)
    }

    long KeyframeIndex = SeekKeyFrameIndex(VideoStreamIndex, FrameIndex);
    int64_t KeyframeTimestamp = -1;

    if(KeyframeIndex > -1)
    {
        KeyframeTimestamp = VideoStreams[VideoStreamIndex]->IndexEntries[KeyframeIndex]->Timestamp;
    }
    else
    {
        //return new VideoFrame(Timestamp, GetTimestampTime(VideoStreamIndex, Timestamp), TargetWidth, TargetHeight, AV_PICTURE_TYPE_I, 128, 0, 0);
        return NULL;
    }

    if(Timestamp < KeyframeTimestamp)
    {
        //return new VideoFrame(Timestamp, GetTimestampTime(VideoStreamIndex, Timestamp), TargetWidth, TargetHeight, AV_PICTURE_TYPE_I, 0, 128, 0);
        return NULL;
    }

    if(GOPBuffer.GetID() != KeyframeIndex)
    {
        FlushBuffer();
        if(!SetStreamPosition(VideoStreamIndex, KeyframeIndex))
        {
            //return new VideoFrame(Timestamp, GetTimestampTime(VideoStreamIndex, Timestamp), TargetWidth, TargetHeight, AV_PICTURE_TYPE_I, 0, 0, 128);
            return NULL;
        }
        GOPBuffer.SetID(KeyframeIndex);
    }

    if(GOPBuffer.GetLastTimestamp() < Timestamp)
    {
        // add frames to gop until timestamp is processed
        AVFrame *pFrameSource = avcodec_alloc_frame();
        AVFrame *pFrameTarget = avcodec_alloc_frame();

        if(pFrameTarget != NULL)
        {
            unsigned char *Buffer = (unsigned char*)av_malloc(avpicture_get_size(TargetPixelFormat, TargetWidth, TargetHeight));
            SwsContext *pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, TargetWidth, TargetHeight, TargetPixelFormat, SWS_FAST_BILINEAR, NULL, NULL, NULL);

            avpicture_fill((AVPicture*)pFrameTarget, Buffer, TargetPixelFormat, TargetWidth, TargetHeight);

            AVPacket packet;
            av_init_packet(&packet);
            int got_frame;
            int64_t FrameTimestamp = Timestamp-1;

            // read packets/frames from file
            while(FrameTimestamp < Timestamp)
            {
                // reached end of file?
                if(av_read_frame(pFormatCtx, &packet))
                {
                    // codec buffer still hold frames?
                    if(got_frame)
                    {
                        // prepare 'flush' packet to receive the
                        // remaining frames from the codec buffer
                        packet.data = NULL;
                        packet.size = 0;
                        packet.stream_index = StreamID;
                    }
                    else
                    {
                        break; // leave loop
                    }
                }

                if(packet.stream_index == StreamID)
                {
                    // avcodec_decode_video()
                    // > 0, packet decoded to frame
                    // = 0, not decoded (i.e. read from codec buffer)
                    // < 0, error
                    if(avcodec_decode_video2(pCodecCtx, pFrameSource, &got_frame, &packet) > -1)
                    {
                        if(got_frame)
                        {
                            // exclude b-frames that belongs to the previous gop, but where ordered after i-frame from this gop (higher dts but lower pts)
                            // first frame in gop must be i-frame
                            if(GOPBuffer.GetCount() > 0 || pFrameSource->pict_type == 1)
                            {
                                FrameTimestamp = pFrameSource->pkt_pts;
                                if(FrameTimestamp == (int64_t)AV_NOPTS_VALUE)
                                {
                                    FrameTimestamp = pFrameSource->pkt_dts;
                                }

                                if(pSwsCtx != NULL)
                                {
                                    sws_scale(pSwsCtx, pFrameSource->data, pFrameSource->linesize, 0, pCodecCtx->height, pFrameTarget->data, pFrameTarget->linesize);

                                    VideoFrame* tex = new VideoFrame(FrameTimestamp, GetTimeFromTimestamp(VideoStreamIndex, FrameTimestamp), TargetWidth, TargetHeight, TargetPixelFormat, pFrameSource->pict_type, (unsigned char*)av_malloc(avpicture_get_size(TargetPixelFormat, TargetWidth, TargetHeight)));
                                    memcpy(tex->Data, pFrameTarget->data[0], tex->DataSize);
                                    GOPBuffer.AddVideoFrame(tex);
                                    tex = NULL;
                                }
                            }
                        }
                    }
                }
                av_free_packet(&packet);
            }
            sws_freeContext(pSwsCtx);
            av_free(Buffer);
        }
        av_free(pFrameTarget);
        av_free(pFrameSource);
    }

    pCodecCtx = NULL;

    return GOPBuffer.GetVideoFrame(Timestamp);
}
