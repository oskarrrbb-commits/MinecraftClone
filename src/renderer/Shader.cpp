#include "Shader.h"
#include <glad/gl.h>
#include <stdexcept>

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        glDeleteShader(vertexShader);
        throw std::runtime_error(infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        throw std::runtime_error(infoLog);
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(m_program);
        throw std::runtime_error(infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}
Shader::~Shader() {
    glDeleteProgram(m_program);
}
Shader::Shader(Shader&& other) noexcept
    : m_program(other.m_program)
{
    other.m_program = 0;
}
unsigned int Shader::id() const {
    return m_program;
}
void Shader::use() const {
    glUseProgram(m_program);
}