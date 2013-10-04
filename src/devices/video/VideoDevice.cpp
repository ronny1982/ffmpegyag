#include "VideoDevice.h"

#ifdef __LINUX__
#include "GLXDevice.h"
#endif
#ifdef __WINDOWS__
#include "WGLDevice.h"
#endif
#include "WXGLDevice.h"

VideoDevice::VideoDevice()
{
    //
}

VideoDevice::~VideoDevice()
{
    //
}

VideoDevice* VideoDevice::Create(VideoDeviceType Type)
{
    if(Type == VideoDeviceGL)
    {
        #ifdef __LINUX__
        return (VideoDevice*)(new GLXDevice());
        #endif
        #ifdef __WINDOWS__
        return (VideoDevice*)(new WGLDevice());
        #endif
    }
    if(Type == VideoDeviceWX)
    {
        return (VideoDevice*)(new WXGLDevice());
    }
    return NULL;
}
