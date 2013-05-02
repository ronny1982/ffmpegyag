#ifndef WINMM_H
#define WINMM_H

#include "AudioDevice.h"

#ifdef __WINDOWS__

//#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

class WinMMDevice
{
    public: WinMMDevice();
    public: virtual ~WinMMDevice();

    // FIXME: change format to AVSampleFormat
    public: bool Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat Format);
    public: void Release();
    public: void Play(unsigned char* FrameData, size_t SampleCount);
    private: int GetWinMMFormat(AVSampleFormat Format);
    private: int GetWinMMSampleSize(AVSampleFormat Format);
    // callback to free block whenever finished playing (static, cannot access members -> access by dwInstance)
    private: static void CALLBACK FreeBlock(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

    private: HWAVEOUT Device;
    /*
     * winMM does not have an internal buffer management
     * -> so we have to implement our own buffer
    */
    private: int block_buffer_size;
    private: int block_buffer_current_count;
    private: int block_buffer_current_index;
    private: WAVEHDR* block_buffer;
    private: bool block_buffer_is_locked;
};

#endif // WINDOWS

#endif // WINMM_H
