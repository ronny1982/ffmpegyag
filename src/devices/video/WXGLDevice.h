#ifndef WXGLDEVICE_H
#define WXGLDEVICE_H

#include "GLDevice.h"
#include <wx/glcanvas.h>

class WXGLDevice : GLDevice
{
    public: WXGLDevice();
    public: virtual ~WXGLDevice();

    public: void* InitWidget(const char* title, int width, int height, int fullscreen);
    public: bool InitContext(void* Widget);
    public: void ReleaseContext();
    public: void ReleaseWidget(void* Widget);
};

#endif // WXGLDEVICE_H
