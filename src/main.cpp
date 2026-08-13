#include <cstdio>
#include <SDL3/SDL.h>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL failed to init: %s\n", SDL_GetError());
        return 1;
    }
    printf("SDL3 initialized successfully\n");
    SDL_Quit();
    return 0;
}