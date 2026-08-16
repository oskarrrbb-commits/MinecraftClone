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
    float m_triangleVertices[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    unsigned int m_shaderProgram = 0;

    void ProcessEvents();
};