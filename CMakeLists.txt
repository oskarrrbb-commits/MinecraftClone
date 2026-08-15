cmake_minimum_required(VERSION 3.20)
project(MinecraftClone)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.12
)
FetchContent_MakeAvailable(SDL3)

add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

add_executable(MinecraftClone
    src/main.cpp
    src/core/SDLContext.cpp
    src/core/Window.cpp
    src/core/GLContext.cpp
    src/core/Application.cpp
)
target_include_directories(MinecraftClone PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)
target_link_libraries(MinecraftClone PRIVATE SDL3::SDL3-static glad)