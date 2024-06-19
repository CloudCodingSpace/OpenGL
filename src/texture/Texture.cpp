#include "Texture.hpp"

Texture::Texture(const char *path, int texNumber)
{
    this->texNumber = texNumber;

    stbi_set_flip_vertically_on_load(true);
    texels = stbi_load(path, &width, &height, &channels, 0);
    if(!texels)
    {
        std::cerr << "Can't load texture!" << std::endl;
        std::exit(-1);
    }

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + (texNumber - 1));
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(channels == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
        glGenerateMipmap(GL_TEXTURE_2D);
    } 
    else if(channels == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else 
    {
        std::cerr << "Can't parse data to the texture buffer!" << std::endl;
        std::exit(-1);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Active()
{
    glActiveTexture(GL_TEXTURE0 + (texNumber - 1));
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Cleanup()
{
    glDeleteTextures(1, &ID);
}

int Texture::getTexNumber()
{
    return texNumber;
}
