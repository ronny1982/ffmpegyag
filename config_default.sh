#!/bin/bash

PKGNAME="ffmpegyag"
PKGVERSION="0.6.0"
PKGSECTION="video"
PKGAUTHOR="Ronny Wegener <wegener.ronny@gmail.com>"
PKGHOMEAGE="http://ffmpegyag.googlecode.com"
PKGDEPENDS="ffmpeg"
PKGDESCRIPTION="A GTK based GUI for ffmpeg
 FFmpegYAG is a GUI for the popular FFmpeg audio/video encoding tool"

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
