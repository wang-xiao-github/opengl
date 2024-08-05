#include "texture.h"
#include <iostream>
Texture::Texture(const std::string& path, unsigned int textureType)
: m_TextureID(0), width(0), height(0), nrChannels(0), m_textureType(textureType)
{
    glGenTextures(1, &m_TextureID);
    glBindTexture(textureType, m_TextureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);  //翻转
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    std::cout << nrChannels << "\n";
    if(data)
    {
            
        if(nrChannels == 4)  glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        else  glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
     
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindTexture(textureType, 0);


}


Texture::~Texture()
{
    glDeleteTextures(1, &m_TextureID);
}
void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(m_textureType, m_TextureID);
}
