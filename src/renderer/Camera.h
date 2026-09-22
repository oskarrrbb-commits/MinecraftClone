#pragma once 
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
class Camera {
public:
    void processKeyboard(const bool* keyState, float deltaTime);
    glm::mat4 getViewMatrix() const;
    Camera();
private:
    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_front;
};