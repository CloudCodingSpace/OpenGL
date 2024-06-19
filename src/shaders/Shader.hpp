#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

class Shader 
{
public:
    Shader() = default;
    Shader(std::string vPath, std::string fPath);
    void Bind();
    void Unbind();
    void PutMat4(glm::mat4 mat, const char* name);
    void PutTex(int slot, const char* name);
    void PutFloat(float val, const char* name);
    void PutInt(int val, const char* name);
    void PutVec3(glm::vec3 vec, const char* name);
    void Cleanup();
    
    GLuint ID, vertShader, fragShader;
private:
    std::string vertSrc, fragSrc;

    std::string get_file_content(const char* path);
    void Gen();
};

#endif