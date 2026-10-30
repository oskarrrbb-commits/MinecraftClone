#pragma once
class Shader {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) = delete;

        void use() const;
        unsigned int id() const;
        
    private:
        unsigned int m_program = 0;
};
