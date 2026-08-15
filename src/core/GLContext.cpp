#include "GLContext.h"
#include <SDL3/SDL.h>
#include <cstdio>
#include "Window.h"
GLContext::GLContext(Window& window) {
    m_context = SDL_GL_CreateContext(window.handle());
    if (!m_context) {
        printf("Failed to create OpenGL context: %s\n", SDL_GetError());
    }
}

GLContext::~GLContext() {
    if (m_context) {
        SDL_GL_DestroyContext(m_context);
    }
}