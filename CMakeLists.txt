cmake_minimum_required(VERSION 3.20)
project(MinecraftClone)

include(FetchContent)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.12
)
FetchContent_MakeAvailable(SDL3)

add_executable(MinecraftClone src/main.cpp)
target_link_libraries(MinecraftClone PRIVATE SDL3::SDL3-static)