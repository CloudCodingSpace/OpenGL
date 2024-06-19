#ifndef TEXTURE_CLASS_HPP
#define TEXTURE_CLASS_HPP

#include <iostream>
#include <stb/stb_image.h>
#include <glad/glad.h>

class Texture
{
public:
    Texture(const char* path, int texNumber);
    void Active();
    void Bind();
    void Unbind();
    void Cleanup();
    int getTexNumber();
private:
    GLuint ID;
    int width, height, channels, texNumber;
    unsigned char* texels;
};

#endif