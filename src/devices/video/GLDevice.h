#ifndef GLDEVICE_H
#define GLDEVICE_H

#include "VideoDevice.h"
#include <GL/gl.h>
#ifdef __WINDOWS__
#include <GL/glext.h>
#endif

class GLDevice : VideoDevice
{
    public: GLDevice();
    public: virtual ~GLDevice();

    public: virtual void* InitWidget(const char* title, int width, int height, int fullscreen) = 0;
    public: virtual bool InitContext(void* Widget) = 0;
    public: virtual void ReleaseContext() = 0;
    public: virtual void ReleaseWidget(void* Widget) = 0;
    public: void SetViewport(int x, int y, int w, int h);
    public: void ClearColour(float red, float green, float blue, float alpha);
    public: void RenderTexture(TexturePanelMap* Mapper, int TextureWidth, int TextureHeight, AVPictureType TextureFormat, unsigned char* TextureData);
    public: void RenderTextureCross(TexturePanelMap* Mapper, float red, float green, float blue, float alpha);
    public: void RenderTextureBlend(TexturePanelMap* Mapper, float red, float green, float blue, float alpha);
    public: void SwapBuffers();
    private: GLint GetAlsaFormat(AVPictureType Format);
};

#endif // GLDEVICE_H
