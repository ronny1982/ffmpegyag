#!/bin/sh

# extract a part of a video
# analyze the streams start time and duration

cd "$(dirname "$0")"
mkdir -p out

FFPROBE="avprobe"
FFMPEG="/home/ronny/Documents/development/ffmpegyag/dist/linux/bin/ffmpeg-1.2.1-hi10-heaac"
FFMPEG="avconv"
FFARGS="-strict experimental -f mp4 -c:a aac -c:v mpeg4"
FILE_IN="/home/ronny/Videos/Agnis Philosophy.mp4"

FILE_OUT=out/Part01
FILE_TYPE=mp4
$FFMPEG -i "$FILE_IN" $FFARGS -ss 00:00:11.000 -t 00:00:12.666 -y "$FILE_OUT.$FILE_TYPE"
$FFPROBE -show_packets "$FILE_OUT.$FILE_TYPE" | grep 'PACKET\|codec_type\|pts_time\|dts_time\|duration_time' > "$FILE_OUT.packets"
$FFPROBE -show_streams "$FILE_OUT.$FILE_TYPE" | grep 'STREAM\|start_time\|duration\|nb_frames' > "$FILE_OUT.streams"

FILE_OUT=out/Part02
FILE_TYPE=mp4
$FFMPEG -i "$FILE_IN" $FFARGS -ss 00:01:01.400 -t 00:00:20.166 -y "$FILE_OUT.$FILE_TYPE"
$FFPROBE -show_packets "$FILE_OUT.$FILE_TYPE" | grep 'PACKET\|codec_type\|pts_time\|dts_time\|duration_time' > "$FILE_OUT.packets"
$FFPROBE -show_streams "$FILE_OUT.$FILE_TYPE" | grep 'STREAM\|start_time\|duration\|nb_frames' > "$FILE_OUT.streams"

FILE_OUT=out/Part03
FILE_TYPE=mp4
$FFMPEG -i "$FILE_IN" $FFARGS -ss 00:02:23.866 -t 00:00:28.200 -y "$FILE_OUT.$FILE_TYPE"
$FFPROBE -show_packets "$FILE_OUT.$FILE_TYPE" | grep 'PACKET\|codec_type\|pts_time\|dts_time\|duration_time' > "$FILE_OUT.packets"
$FFPROBE -show_streams "$FILE_OUT.$FILE_TYPE" | grep 'STREAM\|start_time\|duration\|nb_frames' > "$FILE_OUT.streams"
