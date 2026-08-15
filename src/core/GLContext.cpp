#include "GLContext.h"
#include "Window.h"
#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <cstdio>

GLContext::GLContext(Window& window) {
    m_context = SDL_GL_CreateContext(window.handle());
    if (!m_context) {
        printf("Failed to create OpenGL context: %s\n", SDL_GetError());
        return;
    }

    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    if (version == 0) {
        printf("Failed to initialize GLAD\n");
    } else {
        printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    }
}

GLContext::~GLContext() {
    if (m_context) {
        SDL_GL_DestroyContext(m_context);
    }
}