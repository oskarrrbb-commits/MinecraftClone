#include "Application.h"
#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../world/Chunk.h"
#include "../world/ChunkManager.h"

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;

}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vertexColor, 1.0);
}
)";
    
Application::Application()
    : m_window("MinecraftClone", 1280, 720)
    , m_glContext(m_window)
    , m_camera()
{
    SDL_SetWindowRelativeMouseMode(m_window.handle(), true);
    for (int x = 0; x < 2; ++x) {
        for (int z = 0; z < 2; ++z) {
            m_chunkManager.generateChunk(x, z);
            

        }
    }
    m_chunkManager.getChunk(1, 0)->setBlock(2, 2, 11, BlockType::Air);
    for (int x = 0; x < 2; ++x) {
        for (int z = 0; z < 2; ++z) {
            Chunk* chunkPtr = m_chunkManager.getChunk(x, z);
            MeshData mesh = chunkPtr->buildMesh(ChunkNeighbors{m_chunkManager.getChunk(x + 1, z), m_chunkManager.getChunk(x - 1, z), m_chunkManager.getChunk(x, z + 1), m_chunkManager.getChunk(x, z - 1)});
            printf("%zu\n",mesh.indices.size() / 6);
            m_chunkRenderData.push_back({ Mesh(mesh.vertices, mesh.indices), glm::vec3(x * Chunk::CHUNK_SIZE, 0, z * Chunk::CHUNK_SIZE) });

        }
    }
    

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        printf("Vertex shader compile error: %s\n", infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        printf("Fragment shader compile error: %s\n", infoLog);
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        printf("Shader link error: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Application::run() {
    m_lastFrameTime = SDL_GetTicks();
    while (m_running) {
        Uint64 currentTime = SDL_GetTicks();
        m_deltaTime = (currentTime - m_lastFrameTime) / 1000.0f;
        m_lastFrameTime = currentTime;
        const bool* keyState = SDL_GetKeyboardState(nullptr);
        m_camera.processKeyboard(keyState, m_deltaTime);
        
        ProcessEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(m_shaderProgram);

        int modelLoc = glGetUniformLocation(m_shaderProgram, "model");

        glm::mat4 view = m_camera.getViewMatrix();
        int viewLoc = glGetUniformLocation(m_shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
        int projLoc = glGetUniformLocation(m_shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for (const ChunkRenderData& chunkData : m_chunkRenderData) {
            glm::mat4 chunkModel = glm::translate(glm::mat4(1.0f), chunkData.worldOffset);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(chunkModel));

            chunkData.mesh.draw();
        }
        SDL_GL_SwapWindow(m_window.handle());
    }
}

void Application::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_camera.processMouseMovement(event.motion.xrel, event.motion.yrel);
        }
    }
}