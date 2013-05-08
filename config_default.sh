#!/bin/bash

PKGNAME="ffmpegyag"
PKGVERSION="0.7.3"
PKGSECTION="video"
PKGAUTHOR="Ronny Wegener <wegener.ronny@gmail.com>"
PKGHOMEPAGE="http://ffmpegyag.googlecode.com"
PKGDEPENDS="ffmpeg"
PKGDESCRIPTION="FFmpeg GUI based on wxGTK
 FFmpegYAG is a GUI for the popular FFmpeg audio/video encoding tool.
 .
 Main features:
 .
 + batch encoding
 + realtime preview
 + multi-stream processing
 + file/segment processing"

SRCPATTERN="*.cpp"
SRCDIR="src"
RCPATTERN=""
RCDIR=""
OBJDIR="obj"
DISTROOT="dist/linux"
BINFILE="$DISTROOT/bin/$PKGNAME"

CC="g++"
CFLAGS="
    -c
    -Wall
    -O2
    $(wx-config --static=no --debug=no --cflags)
    "

RC=""
RCFLAGS=""

LD="g++"
LDFLAGS="-s"
LDLIBS="
    $(wx-config --static=no --debug=no --libs --gl-libs)
    -lavformat
    -lavcodec
    -lswscale
    -lasound
    "
