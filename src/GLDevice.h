#ifndef GLDEVICE_H
#define GLDEVICE_H

#include "VideoDevice.h"
#include <GL/gl.h>
#ifdef __WINDOWS__
#include <GL/glext.h>
#endif

class GLDevice/* : VideoDevice*/
{
    public: GLDevice();
    public: virtual ~GLDevice();
};

#endif // GLDEVICE_H
