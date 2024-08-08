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
    void use() const;
    unsigned int getShaderID() const { return m_ShaderProgramID; }
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4& mat4) const;
    void setMat3(const std::string& name, glm::mat3& mat3) const;
    void setVec2(const std::string& name, glm::vec2& vec2) const;
    void setVec3(const std::string& name, const glm::vec3& vec3) const;
    void setVec4(const std::string& name, glm::vec4& vec4) const;

};

