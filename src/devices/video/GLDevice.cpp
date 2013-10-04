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
    glViewport(x, y, w, h);
}

void GLDevice::SetClearColour(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDevice::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDevice::RenderTexture(TexturePanelMap* Mapper, int TextureWidth, int TextureHeight, PixelFormat TextureFormat, unsigned char* TextureData)
{
    GLuint TexturePointer;
    glGenTextures(1, &TexturePointer);
    glBindTexture(GL_TEXTURE_2D, TexturePointer);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GLint TextureGLFormat = GetGLFormat(TextureFormat);
    glTexImage2D(GL_TEXTURE_2D, 0, TextureGLFormat, TextureWidth, TextureHeight, 0, TextureGLFormat, GL_UNSIGNED_BYTE, TextureData);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TexturePointer);

    glBegin(GL_QUADS);
        // top left
        glTexCoord2d(Mapper->TextureLeft, Mapper->TextureTop);
        glVertex2d(Mapper->PanelLeft, Mapper->PanelTop);
        // top right
        glTexCoord2d(Mapper->TextureRight, Mapper->TextureTop);
        glVertex2d(Mapper->PanelRight, Mapper->PanelTop);
        // bottom right
        glTexCoord2d(Mapper->TextureRight, Mapper->TextureBottom);
        glVertex2d(Mapper->PanelRight, Mapper->PanelBottom);
        // bottom left
        glTexCoord2d(Mapper->TextureLeft, Mapper->TextureBottom);
        glVertex2d(Mapper->PanelLeft, Mapper->PanelBottom);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    // this will not free memory of Texture->Data
    glDeleteTextures(1, &TexturePointer);
}

void GLDevice::RenderTextureCross(TexturePanelMap* Mapper, float red, float green, float blue, float alpha)
{
    glColor4f(red, green, blue, alpha);
    glBegin(GL_LINES);
        glVertex2d(Mapper->PanelLeft, Mapper->PanelTop);
        glVertex2d(Mapper->PanelRight, Mapper->PanelBottom);
        glVertex2d(Mapper->PanelRight, Mapper->PanelTop);
        glVertex2d(Mapper->PanelLeft, Mapper->PanelBottom);
    glEnd();
}

void GLDevice::RenderTextureBlend(TexturePanelMap* Mapper, float red, float green, float blue, float alpha)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    glBegin(GL_QUADS);
        glVertex2d(Mapper->PanelLeft, Mapper->PanelTop); // top left
        glVertex2d(Mapper->PanelRight, Mapper->PanelTop); // top right
        glVertex2d(Mapper->PanelRight, Mapper->PanelBottom); // bottom right
        glVertex2d(Mapper->PanelLeft, Mapper->PanelBottom); // bottom left
    glEnd();
    glDisable(GL_BLEND);
}

void GLDevice::SwapBuffers()
{
    glFinish();
}

GLint GLDevice::GetGLFormat(PixelFormat Format)
{
    return GL_RGB;
}
