#pragma once 
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader
{
private:
    unsigned int m_ShaderProgramID;
    ShaderProgramSource loadSource(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    unsigned int createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    unsigned int compileShader(unsigned int shaderType, const std::string& source);
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();
    void use();
    unsigned int getShaderID() { return m_ShaderProgramID; }
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, glm::mat4& mat4);

};

