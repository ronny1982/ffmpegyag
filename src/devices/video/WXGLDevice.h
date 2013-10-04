#ifndef WXGLDEVICE_H
#define WXGLDEVICE_H

#include "GLDevice.h"
#include <wx/glcanvas.h>

// extra class espacially for wxWidgets glCanvas support
class WXGLDevice : GLDevice
{
    public: WXGLDevice();
    public: ~WXGLDevice();

    public: void* CreateWidget(const char* title, int width, int height, bool fullscreen);
    public: void DestroyWidget(void* Widget);
    public: bool Init(void* Widget);
    public: void Release();
    public: void MakeCurrent();
    // extend swap buffers from gl base class
    public: void SwapBuffers();

    private: wxGLCanvas* widget;
};

#endif // WXGLDEVICE_H
