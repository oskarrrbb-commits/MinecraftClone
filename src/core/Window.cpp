#include "Window.h"
#include <SDL3/SDL.h>
#include <cstdio>

Window::Window(const char* title, int width, int height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
    if (!m_window) {
        printf("Failed to create window: %s\n", SDL_GetError());
    }
}
Window::~Window() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
}