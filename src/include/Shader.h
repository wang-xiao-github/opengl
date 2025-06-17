#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource 
{
    std::string VertexShader;
    std::string FragmentShader;
};


 class Shader
 {
 private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, unsigned int> m_UnifromLocationCache;

 public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //set uniforms
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3); 

private:
    
    unsigned int GetUniformLocation(const std::string& name);
    ShaderProgramSource ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

 };
 

 