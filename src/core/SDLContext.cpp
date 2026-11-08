#include "SDLContext.h"
#include <SDL3/SDL.h>
#include <stdexcept>

SDLContext::SDLContext() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(std::string("Failed to initialize SDL: ") + SDL_GetError());
    }
}

SDLContext::~SDLContext() {
    SDL_Quit();
}