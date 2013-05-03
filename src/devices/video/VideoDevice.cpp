#include "VideoDevice.h"

#ifdef __LINUX__
#include "GLXDevice.h"
#endif
#ifdef __WINDOWS__
#include "WGLDevice.h"
#endif

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
    printf("create video device\n");
    if(Type == VideoDeviceGL)
    {
        #ifdef __LINUX__
        return (VideoDevice*)(new GLXDevice());
        #endif
        #ifdef __WINDOWS__
        return (VideoDevice*)(new WGLDevice());
        #endif
    }
    return NULL;
}
