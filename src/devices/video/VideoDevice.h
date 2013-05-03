#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include "../../Libav.h"

struct TexturePanelMap
{
    double TextureTop;
    double TextureBottom;
    double TextureLeft;
    double TextureRight;

    double PanelTop;
    double PanelBottom;
    double PanelLeft;
    double PanelRight;
};

enum VideoDeviceType
{
    VideoDeviceWXGL, // OpenGL using wxGLCanvas (multi platform)
    #ifdef __LINUX__
    //VideoDeviceGLX, // OpenGL using GLX
    #endif
    #ifdef __WINDOWS__
    //VideoDeviceWGL, // OpenGL using WGL
    //VideoDeviceWD3D, // Direct3D using WinAPI
    //VideoDeviceWXD3D, // Direct3D using wx::GetHWND
    #endif
};

class VideoDevice
{
    public: VideoDevice();
    public: virtual ~VideoDevice();

    // static function (instance creation)
    public: static VideoDevice* Create(VideoDeviceType Type);

    // interface functions
    public: virtual void* InitWidget(const char* title, int width, int height, int fullscreen) = 0;
    public: virtual bool InitContext(void* Widget) = 0;
    public: virtual void ReleaseContext() = 0;
    public: virtual void ReleaseWidget(void* Widget) = 0;
    public: virtual void SetViewport(int x, int y, int w, int h) = 0;
    public: virtual void ClearColour(float red, float green, float blue, float alpha) = 0;
    public: virtual void RenderTexture(TexturePanelMap* Mapper, int TextureWidth, int TextureHeight, AVPictureType TextureFormat, unsigned char* TextureData) = 0;
    public: virtual void RenderTextureCross(TexturePanelMap* Mapper, float red, float green, float blue, float alpha) = 0;
    public: virtual void RenderTextureBlend(TexturePanelMap* Mapper, float red, float green, float blue, float alpha) = 0;
    public: virtual void SwapBuffers() = 0;
};

#endif // VIDEODEVICE_H
