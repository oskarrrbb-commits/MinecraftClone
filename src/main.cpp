#include <cstdio>
#include <SDL3/SDL.h>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL failed to init: %s\n", SDL_GetError());
        return 1;
    }
    printf("SDL3 initialized successfully\n");

    SDL_Window* window = SDL_CreateWindow("minecraft clone", 1280, 720, 0);
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}