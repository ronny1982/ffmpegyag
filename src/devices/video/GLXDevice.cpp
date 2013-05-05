#include "GLXDevice.h"

#ifdef __LINUX__

GLXDevice::GLXDevice()
{
    display = NULL;
    widget = NULL;
    context = NULL;
}

GLXDevice::~GLXDevice()
{
    //
}

void* GLXDevice::CreateWidget(const char* title, int width, int height, bool fullscreen)
{
    display = XOpenDisplay(NULL);
    Window x_window_root = DefaultRootWindow(display);
    GLint glxAttr[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, /*GLX_DOUBLEBUFFER,*/ None};
    XVisualInfo* x_visual_info = glXChooseVisual(display, 0, glxAttr); // double buffering is very slow
    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, x_window_root, x_visual_info->visual, AllocNone);
    swa.event_mask = ExposureMask | KeyPressMask;
    Window* x_window_client = new Window();
    *x_window_client = XCreateWindow(display, x_window_root, 0, 0, 640, 360, 0, x_visual_info->depth, InputOutput, x_visual_info->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, *x_window_client);
    XStoreName(display, *x_window_client, "OpenGL - GLX");

    return x_window_client;
}

void GLXDevice::DestroyWidget(void* Widget)
{
    Window* tmp = (Window*)Widget;
    if(tmp)
    {
        if(!display)
        {
            display = XOpenDisplay(NULL);
        }
        // test if internal widget is destroyed
        if(tmp == widget)
        {
            // internal widget is same as widget requested for destruction
            widget = NULL;
        }
        XDestroyWindow(display, *tmp);
        tmp = NULL;
        //Widget = NULL; // statement has no effect, pointer only valid in local scope
    }
}

bool GLXDevice::Init(void* Widget)
{
    // FIXME: display can not be opened again after close, so we avoid opening new one
    if(display)
    {
        if(widget)
        {
            XDestroyWindow(display, *widget);
            widget = NULL;
        }
        if(context)
        {
            glXMakeCurrent(display, None, NULL);
            glXDestroyContext(display, *context);
            context = NULL;
        }
    }
    else
    {
        display = XOpenDisplay(NULL);
    }

    widget = (Window*)Widget;
    if(!widget)
    {
        return false;
    }
    context = new GLXContext();

    XWindowAttributes settings;
    XGetWindowAttributes(display, *widget, &settings);

// FIXME: get correct visual info from display, screen, window
    XVisualInfo* vi = new XVisualInfo();
printf("screen %i\n", XScreenNumberOfScreen(settings.screen));
printf("depth %i\n", settings.depth);
printf("class %i\n", settings.c_class); // FIXME: value seems wrong, should be 4

//XGetVisualInfo(display, vinfo_mask, vinfo_template, nitems_return);
    if(!XMatchVisualInfo(display, XScreenNumberOfScreen(settings.screen)/*XDefaultScreen(display)*/, settings.depth, settings.c_class, vi))
    {
        printf("using default\n");
        GLint glxAttr[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, /*GLX_DOUBLEBUFFER,*/ None};
        vi = glXChooseVisual(display, 0, glxAttr); // double buffering is very slow
    }

printf("vi->screen = %i\n", vi->screen);
printf("vi->depth = %i\n", vi->depth);
printf("vi->class = %i\n", vi->c_class);

    *context = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, *widget, *context);
    XFree(vi);

    //glEnable(GL_DEPTH_TEST);

    return true;
}

void GLXDevice::Release()
{
    if(display)
    {
        // widget belongs to the user, do not destroy !
        /*
        if(widget)
        {
            XDestroyWindow(display, *widget);
            widget = NULL;
        }
        */
        if(context)
        {
            glXMakeCurrent(display, None, NULL);
            glXDestroyContext(display, *context);
            context = NULL;
        }
        XCloseDisplay(display);
        display = NULL;
    }
}

void GLXDevice::MakeCurrent()
{
    glXMakeCurrent(display, *widget, *context);
}

void GLXDevice::SwapBuffers()
{
    glXSwapBuffers(display, *widget);
    GLDevice::SwapBuffers(); // must be used on single buffering & double buffering
}

#endif
