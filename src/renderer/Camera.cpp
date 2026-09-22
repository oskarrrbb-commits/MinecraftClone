#include "Camera.h"
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
    : m_position(4.0f, 3.0f, 6.0f)
    , m_up(0.0f, 1.0f, 0.0f)
    , m_front(-4.0f, -3.0f, -6.0f)
{
}
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}
    
