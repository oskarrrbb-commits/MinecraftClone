#pragma once 
#include "Window.h"
#include "SDLContext.h"

class Application {
public:
    Application();
    void run();
private:
    SDLContext m_sdl;
    Window m_window;
    bool m_running = true;

    void ProcessEvents();
};