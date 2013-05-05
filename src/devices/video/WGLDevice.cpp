#include "WGLDevice.h"

#ifdef __WINDOWS__

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

void WGLDevice::DestroyWidget(void* Widget)
{
    //
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

void WGLDevice::SwapBuffers()
{
    //wglSwapuffer(widget, context);
    GLDevice::SwapBuffers();
}
#endif // WINDOWS
