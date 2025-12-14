#pragma once
#include <string>
#include <glm.hpp>

class Shader {
public:
    unsigned int ID;

    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
    std::string loadShaderFromFile(const char* filePath);
};
