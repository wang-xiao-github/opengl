#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
: m_Count  (count)
{
    GLCall(glGenBuffers(1, &m_RendererID)); //生成一个缓冲区
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //绑定缓冲区，第一个参数是目标，意思是生成的buffer是干嘛用的，这里是当数组；第二个参数传入buffer id
    //第一个参数同样是目标；第二个，指定缓冲区的新数据存储的字节大小；第三个数实际属性；第四个，绘制方式，静态，动态等，静态修改一次，每帧不会变，
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_RendererID)); 
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //绑定缓冲区，第一个参数是目标，意思是生成的buffer是干嘛用的，这里是当数组；第二个参数传入buffer id

}
void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); 
}