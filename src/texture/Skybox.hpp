#ifndef SKYBOX_CLASS_HPP
#define SKYBOX_CLASS_HPP

#include "../shaders/Shader.hpp"
#include "../camera/Camera.hpp"

#include <vector>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>
#include <glm/glm.hpp>

class Skybox 
{
public:
    Skybox(std::vector<std::string> filePaths);
    void Render(Camera& camera);
    void Cleanup();

    Shader shader;
private:
    GLuint ID, vaoID, vboID, eboID;
    glm::mat4 view;
    glm::mat4 proj;
};

#endif