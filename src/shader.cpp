#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
: m_ShaderProgramID(0)
{
    ShaderProgramSource source = loadSource(vertexShaderPath, fragmentShaderPath);
    m_ShaderProgramID = createShaderProgram(source.VertexShader, source.FragmentShader);
    // glUseProgram(m_ShaderProgramID);
}
Shader::~Shader()
{
    glDeleteProgram(m_ShaderProgramID);
}
void Shader::use()
{
    glUseProgram(m_ShaderProgramID);
}
ShaderProgramSource Shader::loadSource(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::ifstream vertexSource(vertexShaderPath);
    std::ifstream fragmentSource(fragmentShaderPath);

    if(!vertexSource)  std::cout << "Load vertex source error !\n"; 
    else if (!fragmentSource) std::cout << "Load fragment source error !\n"; 
    std::string line;
    std::stringstream ss[2];
    while(getline(vertexSource, line))  ss[0] << line << "\n";
    while(getline(fragmentSource, line))  ss[1] << line << "\n";

    vertexSource.close();
    fragmentSource.close();
    return {ss[0].str(), ss[1].str()};
}
unsigned int Shader::createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int shaderProgramID = glCreateProgram();
    unsigned int vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return shaderProgramID;
}
unsigned int Shader::compileShader(unsigned int shaderType, const std::string& source)
{
    unsigned int shaderID = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, NULL);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR: compileShader ("<< shaderType << ") failed \n" << infoLog << std::endl;
    }

    return shaderID;

}

void Shader::setBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_ShaderProgramID, name.c_str()), value);
}
void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_ShaderProgramID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_ShaderProgramID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, glm::mat4& mat4)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}