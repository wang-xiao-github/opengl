#pragma once
#include <glad/glad.h>
#include "stb_image/stb_image.h"
#include <string>

class Texture
{
private:
    unsigned int m_TextureID;
    unsigned int m_textureType;
    int width, height, nrChannels;
public:
    Texture(const std::string& path, unsigned int textureType);
    ~Texture();
    void bind(unsigned int slot = 0) const;
};

