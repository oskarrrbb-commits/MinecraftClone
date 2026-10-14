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
    unsigned int m_shaderProgram = 0;
    std::vector<ChunkRenderData> m_chunkRenderData;
    ChunkManager m_chunkManager;
    Uint64 m_lastFrameTime = 0;
    float m_deltaTime = 0.0f;
    void ProcessEvents();
};
