#include "GLContext.h"
#include "Window.h"
#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <cstdio>
#include <stdexcept>

GLContext::GLContext(Window& window) {
    m_context = SDL_GL_CreateContext(window.handle());
    if (!m_context) {
        throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
    }

    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    if (version == 0) {
        SDL_GL_DestroyContext(m_context);
        throw std::runtime_error(std::string("Failed initalize GLAD"));
    } else {
        printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    }
}

GLContext::~GLContext() {
    if (m_context) {
        SDL_GL_DestroyContext(m_context);
    }
}