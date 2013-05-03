#include "GLDevice.h"

GLDevice::GLDevice()
{
    //
}

GLDevice::~GLDevice()
{
    //
}

void GLDevice::SetViewport(int x, int y, int w, int h)
{
    //
}

void GLDevice::ClearColour(float red, float green, float blue, float alpha)
{
    //
}

void GLDevice::RenderTexture(TexturePanelMap* Mapper, int TextureWidth, int TextureHeight, AVPictureType TextureFormat, unsigned char* TextureData)
{
    //
}

void GLDevice::RenderTextureCross(TexturePanelMap* Mapper, float red, float green, float blue, float alpha)
{
    //
}

void GLDevice::RenderTextureBlend(TexturePanelMap* Mapper, float red, float green, float blue, float alpha)
{
    //
}

void GLDevice::SwapBuffers()
{
    //
}

GLint GLDevice::GetAlsaFormat(AVPictureType Format)
{
    return GL_RGB;
}
