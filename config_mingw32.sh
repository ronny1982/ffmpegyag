#!/bin/bash

# import setings from config-default
. ./config_default.sh

# overwrite settings from config-default
RCPATTERN="app.rc"
RCDIR="res"
DISTROOT="build/msw"
BINFILE="$DISTROOT/bin/$PKGNAME.exe"

CFLAGS="
    -c
    -Wall
    -O2
    -D__GNUWIN32__
    -D__WXMSW__
    -DwxUSE_UNICODE
    -Iinclude/msw
    -Ilib/msw/wx/mswu
    -Iinclude/msw/ffmpeg
    "

RC="windres.exe"
RCFLAGS="
    -J rc
    -O coff
    -F pe-i386
    -Iinclude/msw
    "

LDFLAGS="
    -s
    -static
    -static-libgcc
    -static-libstdc++
    -mwindows
    "
LDLIBS="
    -Llib/msw/wx
    -lwx_mswu-2.8
    -lwx_mswu_gl-2.8
    -lwxexpat-2.8
    -lwxregexu-2.8
    -lwxpng-2.8
    -lwxjpeg-2.8
    -lwxtiff-2.8
    -lwxzlib-2.8
    -Llib/msw/ffmpeg
    -lavformat.dll
    -lavcodec.dll
    -lswscale.dll
    -lavutil.dll
    -L/mingw/lib
    -lwinspool
    -lole32
    -loleaut32
    -luuid
    -lcomctl32
    -lopengl32
    -lwinmm
    "
