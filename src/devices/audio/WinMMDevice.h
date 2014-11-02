#ifndef WINMM_H
#define WINMM_H

#include "AudioDevice.h"

#ifdef __WINDOWS__

#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
//#include <ksmedia.h>
#define KSDATAFORMAT_SUBTYPE_NONE       (GUID) {0x00000000,0x0000,0x0010,{0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71}}
#define KSDATAFORMAT_SUBTYPE_PCM        (GUID) {0x00000001,0x0000,0x0010,{0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71}}
#define KSDATAFORMAT_SUBTYPE_IEEE_FLOAT (GUID) {0x00000003,0x0000,0x0010,{0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71}}

class WinMMDevice : public AudioDevice
{
    public: WinMMDevice();
    public: virtual ~WinMMDevice();

    // FIXME: change format to AVSampleFormat
    public: bool Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat Format);
    public: void Release();
    public: void Play(unsigned char* FrameData, size_t SampleCount);
    private: GUID GetWinMMFormat(AVSampleFormat Format);
    private: int GetWinMMSampleSize(AVSampleFormat Format);
    // callback to free block whenever finished playing (static, cannot access members -> access by dwInstance)
    private: static void CALLBACK FreeBlock(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

    private: HWAVEOUT Device;
    private: WAVEFORMATEXTENSIBLE HardwareInfo;
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
