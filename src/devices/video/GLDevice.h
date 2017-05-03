#ifndef GLDEVICE_H
#define GLDEVICE_H

#include "VideoDevice.h"
#include <GL/gl.h>

class GLDevice : VideoDevice
{
    public: GLDevice();
    public: virtual ~GLDevice();

    public: virtual void* CreateWidget(const char* title, int width, int height, bool fullscreen) = 0;
    public: virtual void DestroyWidget(void* Widget) = 0;
    public: virtual bool Init(void* Widget) = 0;
    public: virtual void Release() = 0;
    public: virtual void MakeCurrent() =0;
    public: void SetViewport(int x, int y, int w, int h);
    public: void SetClearColour(float red, float green, float blue, float alpha);
    public: void Clear();
    public: void RenderTexture(TexturePanelMap* Mapper, int TextureWidth, int TextureHeight, AVPixelFormat TextureFormat, unsigned char* TextureData);
    public: void RenderTextureCross(TexturePanelMap* Mapper, float red, float green, float blue, float alpha);
    public: void RenderTextureBlend(TexturePanelMap* Mapper, float red, float green, float blue, float alpha);
    public: void SwapBuffers();
    private: GLint GetGLFormat(AVPixelFormat Format);
};

#endif // GLDEVICE_H
