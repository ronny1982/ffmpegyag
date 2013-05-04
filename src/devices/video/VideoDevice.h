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
    VideoDeviceGL,
    VideoDeviceWX,
    #ifdef __LINUX__
    //
    #endif
    #ifdef __WINDOWS__
    //VideoDeviceD3D,
    #endif
};

class VideoDevice
{
    public: VideoDevice();
    public: virtual ~VideoDevice();

    // static function (instance creation)
    public: static VideoDevice* Create(VideoDeviceType Type);

    // interface functions
    public: virtual void* CreateWidget(const char* title, int width, int height, bool fullscreen) = 0;
    public: virtual void DestroyWidget(void* Widget) = 0;
    public: virtual bool Init(void* Widget) = 0;
    public: virtual void Release() = 0;
    public: virtual void MakeCurrent() = 0;
    public: virtual void SetViewport(int x, int y, int w, int h) = 0;
    public: virtual void SetClearColour(float red, float green, float blue, float alpha) = 0;
    public: virtual void Clear() = 0;
    public: virtual void RenderTexture(TexturePanelMap* Mapper, int TextureWidth, int TextureHeight, PixelFormat TextureFormat, unsigned char* TextureData) = 0;
    public: virtual void RenderTextureCross(TexturePanelMap* Mapper, float red, float green, float blue, float alpha) = 0;
    public: virtual void RenderTextureBlend(TexturePanelMap* Mapper, float red, float green, float blue, float alpha) = 0;
    public: virtual void SwapBuffers() = 0;
};

#endif // VIDEODEVICE_H
