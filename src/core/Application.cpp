#include "Application.h"
#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <cstdio>

Application::Application()
    : m_window("MinecraftClone", 1280, 720)
    , m_glContext(m_window)
{
}

void Application::run() {
    while (m_running) {
        ProcessEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(m_window.handle());
    }
}

void Application::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
    }
}