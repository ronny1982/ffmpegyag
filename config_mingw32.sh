#!/bin/bash

# import setings from config-default
. ./config_default.sh

# overwrite settings from config-default
RCPATTERN="app.rc"
RCDIR="res"
DISTROOT="build/msw"
BINFILE="$DISTROOT/bin/$PKGNAME.exe"

CC="mingw32-g++.exe"
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

LD="mingw32-g++.exe"
LDFLAGS="
    -s
    -static-libgcc
    -static-libstdc++
    -mwindows
    "
LDLIBS="
    -Llib/msw/wx
    -lwxmsw28u
    -lwxmsw28u_gl
    -lwxexpat
    -lwxregexu
    -lwxpng
    -lwxjpeg
    -lwxtiff
    -lwxzlib
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
