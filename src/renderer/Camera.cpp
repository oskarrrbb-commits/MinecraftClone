#include "Camera.h"
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL3/SDL.h>
#define MOVEMENT_SPEED 4.5f
Camera::Camera()
    : m_position(4.0f, 3.0f, 6.0f)
    , m_up(0.0f, 1.0f, 0.0f)
    , m_front(0.0f, 0.0f, -1.0f)
{
}
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(const bool* keyState, float deltaTime) {
    float velocity = MOVEMENT_SPEED * deltaTime;
    if (keyState[SDL_SCANCODE_W]) {
        m_position += m_front * velocity;
    }
    if (keyState[SDL_SCANCODE_S]) {
        m_position -= m_front * velocity;
    }
    if (keyState[SDL_SCANCODE_A]) {
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * velocity;
    }
    if (keyState[SDL_SCANCODE_D]) {
        m_position += glm::normalize(glm::cross(m_front, m_up)) * velocity;
    }
}