#include "VideoDevice.h"

#include "WXGLDevice.h"
#ifdef __LINUX__
//#include "GLXDevice.h"
#endif
#ifdef __WINDOWS__
//#include "WGLDevice.h"
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
    return NULL;
}
