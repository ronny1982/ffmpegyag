#include "WinMMDevice.h"

#ifdef __WINDOWS__

WinMMDevice::WinMMDevice()
{
    //
}

WinMMDevice::~WinMMDevice()
{
    Release();
}

bool WinMMDevice::Init(unsigned int SampleRate, unsigned int ChannelCount, AVSampleFormat Format)
{
    HardwareInfo.Format.nSamplesPerSec = (int)SampleRate;
    HardwareInfo.Format.wBitsPerSample = GetWinMMSampleSize(Format);
    HardwareInfo.Format.nChannels = (int)ChannelCount;
    HardwareInfo.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    HardwareInfo.Format.nBlockAlign = (HardwareInfo.Format.wBitsPerSample >> 3) * HardwareInfo.Format.nChannels;
    HardwareInfo.Format.nAvgBytesPerSec = HardwareInfo.Format.nBlockAlign * HardwareInfo.Format.nSamplesPerSec;
    HardwareInfo.Format.cbSize = 22; // size of extended data (following 3 members...)
    HardwareInfo.Samples.wValidBitsPerSample = HardwareInfo.Format.wBitsPerSample;
    HardwareInfo.dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT; // KSAUDIO_SPEAKER_STEREO
    HardwareInfo.SubFormat = GetWinMMFormat(Format);

    block_buffer_size = 8;
    block_buffer_current_count = 0;
    block_buffer_current_index = 0;
    block_buffer = (WAVEHDR*)malloc(sizeof(WAVEHDR) * block_buffer_size);
    memset(block_buffer, 0, sizeof(WAVEHDR) * block_buffer_size); // set everything to 0
    block_buffer_is_locked = false;

    if(waveOutOpen(&Device, WAVE_MAPPER, &HardwareInfo.Format, (DWORD_PTR)WinMMDevice::FreeBlock, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
    {
        return false;
    }
    return true;
}

void WinMMDevice::Release()
{
    if(!block_buffer)
    {
        return;
    }

    // simple mutex/semaphore implementation
    while(block_buffer_is_locked){}
    block_buffer_is_locked = true;

    // free block_buffer
    for(int i=0; i<block_buffer_size; i++)
    {
        if(block_buffer[i].lpData)
        {
            free(block_buffer[i].lpData);
            block_buffer[i].lpData = NULL;
        }
    }
    block_buffer_current_count = 0;
    block_buffer_current_index = 0;
    free(block_buffer);
    block_buffer = NULL;

    waveOutReset(Device); // != MMSYSERR_NOERROR
    waveOutClose(Device); // != MMSYSERR_NOERROR

    block_buffer_is_locked = false;
}

void WinMMDevice::Play(unsigned char* FrameData, size_t SampleCount)
{
    while(block_buffer_current_count >= block_buffer_size){}
    // simple mutex/semaphore implementation
    while(block_buffer_is_locked){}
    if(!block_buffer)
    {
        return;
    }
    block_buffer_is_locked = true;
    WAVEHDR* current_block = &block_buffer[(block_buffer_current_index + block_buffer_current_count) % block_buffer_size];
    current_block->dwBufferLength = (long)(SampleCount * HardwareInfo.Format.nBlockAlign);
    current_block->lpData = (char*)FrameData;
    waveOutPrepareHeader(Device, current_block, sizeof(WAVEHDR));
    waveOutWrite(Device, current_block, sizeof(WAVEHDR));
    block_buffer_current_count++;
    block_buffer_is_locked = false;
}

GUID WinMMDevice::GetWinMMFormat(AVSampleFormat Format)
{
    switch(Format)
    {
        case AV_SAMPLE_FMT_U8:   return KSDATAFORMAT_SUBTYPE_PCM;
        case AV_SAMPLE_FMT_S16:  return KSDATAFORMAT_SUBTYPE_PCM;
        case AV_SAMPLE_FMT_S32:  return KSDATAFORMAT_SUBTYPE_PCM;
        case AV_SAMPLE_FMT_FLT:  return KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
        case AV_SAMPLE_FMT_DBL:  return KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
        case AV_SAMPLE_FMT_U8P:  return KSDATAFORMAT_SUBTYPE_PCM;
        case AV_SAMPLE_FMT_S16P: return KSDATAFORMAT_SUBTYPE_PCM;
        case AV_SAMPLE_FMT_S32P: return KSDATAFORMAT_SUBTYPE_PCM;
        case AV_SAMPLE_FMT_FLTP: return KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
        case AV_SAMPLE_FMT_DBLP: return KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
        default: return KSDATAFORMAT_SUBTYPE_NONE;
    }
}

int WinMMDevice::GetWinMMSampleSize(AVSampleFormat Format)
{
    switch(Format)
    {
        case AV_SAMPLE_FMT_U8:   return 8;
        case AV_SAMPLE_FMT_S16:  return 16;
        case AV_SAMPLE_FMT_S32:  return 32;
        case AV_SAMPLE_FMT_FLT:  return 32;
        case AV_SAMPLE_FMT_DBL:  return 64;
        case AV_SAMPLE_FMT_U8P:  return 8;
        case AV_SAMPLE_FMT_S16P: return 16;
        case AV_SAMPLE_FMT_S32P: return 32;
        case AV_SAMPLE_FMT_FLTP: return 32;
        case AV_SAMPLE_FMT_DBLP: return 64;
        default: return 0;
    }
}

void CALLBACK WinMMDevice::FreeBlock(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    if(uMsg == WOM_DONE)
    {
        WinMMDevice* Device = (WinMMDevice*)dwInstance;
        // simple mutex/semaphore implementation
        while(Device && Device->block_buffer && Device->block_buffer_is_locked){}
        if(!Device || !Device->block_buffer)
        {
            return;
        }
        Device->block_buffer_is_locked = true;
        WAVEHDR* current_block = &(Device->block_buffer[Device->block_buffer_current_index]);
        while(waveOutUnprepareHeader(Device->Device, current_block, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING){}
        free(current_block->lpData);
        current_block->lpData = NULL;
        current_block->dwBufferLength = 0;
        Device->block_buffer_current_index = (Device->block_buffer_current_index + 1) % Device->block_buffer_size;
        current_block = NULL;
        Device->block_buffer_current_count--;
        Device->block_buffer_is_locked = false;
        Device = NULL;
    }
}

#endif // WINDOWS
