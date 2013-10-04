#ifndef GLXDEVICE_H
#define GLXDEVICE_H

#include "GLDevice.h"

#ifdef __LINUX__

#include <GL/glx.h>

class GLXDevice : GLDevice
{
    public: GLXDevice();
    public: ~GLXDevice();

    public: void* CreateWidget(const char* title, int width, int height, bool fullscreen);
    public: void DestroyWidget(void* Widget);
    public: bool Init(void* Widget);
    public: void Release();
    public: void MakeCurrent();
    // extend swap buffers from gl base class
    public: void SwapBuffers();

    private: Display* display;
    private: Window* widget;
    private: GLXContext* context;
};

#endif // LINUX

#endif // GLXDEVICE_H
