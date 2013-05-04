#include "WXGLDevice.h"

WXGLDevice::WXGLDevice()
{
    widget = NULL;
}

WXGLDevice::~WXGLDevice()
{
    //
}

void* WXGLDevice::CreateWidget(const char* title, int width, int height, bool fullscreen)
{
    // TODO: create wxWidgets window
    return NULL;
}

void WXGLDevice::DestroyWidget(void* Widget)
{
    Release();
    wxGLCanvas* tmp = (wxGLCanvas*)Widget;
    wxDELETE(tmp);
    tmp = NULL;
    Widget = NULL;
}

bool WXGLDevice::Init(void* Widget)
{
    widget = (wxGLCanvas*)Widget;
    if(widget && widget->GetContext())
    {
        return true;
    }
    return false;
}

void WXGLDevice::Release()
{
    //
}

void WXGLDevice::MakeCurrent()
{
    widget->SetCurrent();
}

void WXGLDevice::SwapBuffers()
{
    // FIXME: only swap when doublebuffering is enabled!
    #ifdef __WINDOWS__
    widget->SwapBuffers();
    #endif
    GLDevice::SwapBuffers();
}
