#pragma once
#include <SDL3/SDL.h>

class Window;

class GLContext {
public:
    GLContext(Window& window);
    ~GLContext();

    GLContext(const GLContext&) = delete;
    GLContext& operator=(const GLContext&) = delete;

private:
    SDL_GLContext m_context = nullptr;
};