#include "Window.h"
#include <SDL3/SDL.h>
#include <cstdio>

Window::Window(const char* title, int width, int height) {
    m_window = SDL_CreateWindow(title, width, height, 0);
    if (!m_window) {
        printf("Failed to create window: %s\n", SDL_GetError());
    }
}
Window::~Window() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
}