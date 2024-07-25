#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <sstream>
#include <fstream>



Shader::Shader(const std::string& filepath) 
: m_FilePath(filepath), m_RendererID(0)
{
//读取shader program的字符串
ShaderProgramSource source = ParseShader(filepath);
//创建shader
m_RendererID= CreateShader(source.VertexShader, source.FragmentShader);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void  Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void  Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void  Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int  Shader::GetUniformLocation(const std::string& name)
{

    if(m_UnifromLocationCache.find(name) != m_UnifromLocationCache.end())
        return m_UnifromLocationCache[name];

    GLCall(unsigned int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
    {
    std::cout << "Warning: uniform "<< name <<"doesn't exist!\n";
    }
    else
        m_UnifromLocationCache[name] = location;
    return location;
}


ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    // stream.close();
    return { ss[0].str(), ss[1].str() };
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); //创建一个shader，返回id
    const char* src = source.c_str(); //返回源码的首地址

    glShaderSource(id, 1, &src, nullptr); //shader的id，有几个源码，指向实际的指针
    glCompileShader(id); //传入着色器id，编译

    //TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Fileed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message <<std::endl;

        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //指定需要附加的程序 
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    //链接程序
    glLinkProgram(program);

    glValidateProgram(program);

    //删除shader其他的中间等文件
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
