cmake_minimum_required(VERSION 3.20)
project(MinecraftClone)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

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

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    googletest 
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(glad STATIC external/glad/src/gl.c)
add_library(world STATIC src/world/Chunk.cpp src/world/ChunkManager.cpp)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

target_link_libraries(world PUBLIC glm::glm)
target_compile_features(world PRIVATE cxx_std_17)
set_target_properties(world PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(world PRIVATE -Wall -Wextra)

add_executable(world_tests 
    tests/ChunkTests.cpp
    tests/FaceTableTests.cpp
)
target_link_libraries(world_tests PRIVATE world GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(world_tests)
target_compile_features(world_tests PRIVATE cxx_std_17)
set_target_properties(world_tests PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(world_tests PRIVATE -Wall -Wextra)

add_executable(MinecraftClone
    src/main.cpp
    src/core/SDLContext.cpp
    src/core/Window.cpp
    src/core/GLContext.cpp
    src/renderer/Camera.cpp
    src/core/Application.cpp
    src/renderer/Mesh.cpp
    src/renderer/Shader.cpp
)

target_compile_features(MinecraftClone PRIVATE cxx_std_17)
set_target_properties(MinecraftClone PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(MinecraftClone PRIVATE -Wall -Wextra)

target_link_libraries(MinecraftClone PRIVATE SDL3::SDL3-static glad glm::glm world)
target_link_options(MinecraftClone PRIVATE -static-libgcc -static-libstdc++ -static)