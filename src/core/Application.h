#pragma once 
#include "Window.h"
#include "SDLContext.h"
#include "GLContext.h"

class Application {
public:
    Application();
    void run();
private:
    SDLContext m_sdl;
    Window m_window;
    GLContext m_glContext;
    bool m_running = true;
    

    void ProcessEvents();
};