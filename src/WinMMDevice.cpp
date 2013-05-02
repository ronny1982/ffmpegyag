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
    // TODO:
    // WAVE_FORMAT_PCM only for 1/2 channel and 8/16 bit
    // WAVE_FORMAT_EXTENSIBLE support for ieee and multichannel
    WAVEFORMATEX HardwareInfo;
    HardwareInfo.nSamplesPerSec = SampleRate;
    HardwareInfo.wBitsPerSample = GetWinMMSampleSize(Format);
    HardwareInfo.nChannels = ChannelCount;
    HardwareInfo.cbSize = 0;
    HardwareInfo.wFormatTag = WAVE_FORMAT_PCM;
    HardwareInfo.nBlockAlign = (HardwareInfo.wBitsPerSample >> 3) * ChannelCount;
    HardwareInfo.nAvgBytesPerSec = HardwareInfo.nBlockAlign * SampleRate;

    block_buffer_size = 8;
    block_buffer_current_count = 0;
    block_buffer_current_index = 0;
    block_buffer = (WAVEHDR*)malloc(sizeof(WAVEHDR) * block_buffer_size);
    memset(block_buffer, 0, sizeof(WAVEHDR) * block_buffer_size); // set everything to 0
    block_buffer_is_locked = false;

    if(waveOutOpen(&Device, WAVE_MAPPER, &HardwareInfo, (DWORD_PTR)WinMMDevice::FreeBlock, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
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
    current_block->dwBufferLength = SampleCount;
    current_block->lpData = (char*)FrameData;
    waveOutPrepareHeader(Device, current_block, sizeof(WAVEHDR));
    waveOutWrite(Device, current_block, sizeof(WAVEHDR));
    block_buffer_current_count++;
    block_buffer_is_locked = false;
}

int WinMMDevice::GetWinMMFormat(AVSampleFormat Format)
{
    // TODO: change to real libav AVSampleFormat
    return 0;
}

int WinMMDevice::GetWinMMSampleSize(AVSampleFormat Format)
{
    // TODO: change to real libav AVSampleFormat
    return 16;
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

/*
// DEMO APPLICATION
int main(int argc, char* argv[])
{
    int channels = 2;
    int samplesize = 2; // -> short values
    int samplecount = 1600;
    int samplerate = 44100;
    AVSampleFormat sampleformat = AV_FMT_S16;

    WinMMDevice* AudioDevice = new WinMMDevice();

    if(AudioDevice->Init(samplerate, channels, sampleformat))
    {
        for(int i=0; i<32; i++)
        {
            short* data = (short*)malloc(channels*samplesize*samplecount);
            for(int i=0; i<channels*samplecount; i+=channels)
            {
                // fill all channels
                data[i+0] = (short)(4*(i%80)); // left channel
                data[i+1] = (short)(2*(i%160)); // right channel
            }
            AudioDevice->Play((unsigned char*)data, channels*samplesize*samplecount);
            data = NULL;
        }
    }
    AudioDevice->Release();
    delete AudioDevice;
}
*/

#endif // WINDOWS
