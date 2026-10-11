#pragma once 
#include "Window.h"
#include "SDLContext.h"
#include "GLContext.h"
#include "../renderer/Camera.h"
#include <SDL3/SDL.h>
#include "../world/ChunkManager.h"
#include <vector>
struct ChunkRenderData {
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
    unsigned int indexCount = 0;
    glm::vec3 worldOffset;
};
class Application {
public:
    Application();
    void run();
private:
    SDLContext m_sdl;
    Window m_window;
    GLContext m_glContext;
    Camera m_camera;
    bool m_running = true;
    float m_cubeVertices[144] = {
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    };
    unsigned int m_indices[36] = {
        0,1,2,   2,3,0,      
        4,5,6,   6,7,4,      
        8,9,10,  10,11,8,    
        12,13,14, 14,15,12,  
        16,17,18, 18,19,16,  
        20,21,22, 22,23,20   
    };
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    unsigned int m_shaderProgram = 0;
    unsigned int m_ebo = 0;
    std::vector<ChunkRenderData> m_chunkRenderData;
    ChunkManager m_chunkManager;
    Uint64 m_lastFrameTime = SDL_GetTicks();
    float m_deltaTime = 0.0f;
    void ProcessEvents();
};