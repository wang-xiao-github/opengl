#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray(/* args */)
{
        GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
   GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const 
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const 
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    //设置布局
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i)); //启用
        //参数分别为：缓冲区中实际属性的索引对type的计数；归一化（比如颜色0~255归一化成0~1的浮点数）；每个顶点之间的字节数，指向实际属性的指针
        GLCall(glVertexAttribPointer(i, element.count, element.type, 
                        element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
   
}

