#pragma once 
#include <glm/glm.hpp>
class Camera {
public:
    glm::mat4 getViewMatrix() const;
    Camera();
private:
    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_front;
};