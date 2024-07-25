#pragma once
#include <GL/glew.h> 

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//使用宏定义错误
#define ASSERT(x) if (!(x)) __builtin_trap();  //__builtin_trap是mac平台特有的
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//清楚之前的错误
void GLClearError();
//检查错误
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    Renderer(/* args */);
    ~Renderer();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader ) const;
    void Clear() const;

};



