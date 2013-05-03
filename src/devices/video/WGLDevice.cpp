#ifdef __WINDOWS__

#include "WGLDevice.h"

WGLDevice::WGLDevice()
{
    //
}

WGLDevice::~WGLDevice()
{
    //
}

void* WGLDevice::CreateWidget(const char* title, int width, int height, bool fullscreen)
{
    widget = NULL;
    return widget;
}

bool WGLDevice::Init(void* Widget)
{
    widget = (HDC)Widget;
    if(widget)
    {
        context = wglCreateContext(widget);
        if(context)
        {
            return true;
        }
    }
    return false;
}

void WGLDevice::Release()
{
    //
}

void WGLDevice::MakeCurrent()
{
    wglMakeCurrent(widget, context);
}

#endif // WINDOWS
