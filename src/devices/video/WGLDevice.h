#ifndef WGLDEVICE_H
#define WGLDEVICE_H

#include "GLDevice.h"

#ifdef __WINDOWS__

#include <windows.h>
#include <GL/glext.h>

class WGLDevice : GLDevice
{
    public: WGLDevice();
    public: ~WGLDevice();

    public: void* CreateWidget(const char* title, int width, int height, bool fullscreen);
    public: void DestroyWidget(void* Widget);
    public: bool Init(void* Widget);
    public: void Release();
    public: void MakeCurrent();
    // extend swap buffers from gl base class
    public: void SwapBuffers();

    private: HDC widget;
    private: HGLRC context;
};

#endif // WINDOWS

#endif // WXGLDEVICE_H
