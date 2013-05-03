#ifndef WGLDEVICE_H
#define WGLDEVICE_H

#ifdef __WINDOWS__

#include "GLDevice.h"
#include <GL/glext.h>

class WGLDevice : GLDevice
{
    public: WXGLDevice();
    public: ~WXGLDevice();

    public: void* CreateWidget(const char* title, int width, int height, bool fullscreen);
    public: bool Init(void* Widget);
    public: void Release();
    public: void MakeCurrent();

    private: HDC widget;
    private: HGLRC context;
};

#endif // WINDOWS

#endif // WXGLDEVICE_H
