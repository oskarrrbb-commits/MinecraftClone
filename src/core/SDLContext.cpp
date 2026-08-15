#include "SDLContext.h"
#include <SDL3/SDL.h>
#include <cstdio>

SDLContext::SDLContext() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL failed to init: %s\n", SDL_GetError());
    }
}

SDLContext::~SDLContext() {
    SDL_Quit();
}