#ifndef CAMERA_CLASS_HPP
#define CAMERA_CLASS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shaders/Shader.hpp"

#include <math.h>

class Camera 
{
public:
    Camera(glm::vec3 pos, GLFWwindow* window);
    void Update(Shader& shader);
    void Input();
    void PutMatrices(Shader& shader);
    glm::mat4 GetViewMat();
    glm::mat4 GetModelMat();
    glm::mat4 GetProjMat();

    glm::vec3 pos, front, up;
    glm::mat4 view, proj, model;
    double crntX, crntY, lastX = 400, lastY = 300;
    float yaw = -90.0f, pitch = 0.0f, speed = 0.03f, sensitivity = 0.1f;
    GLFWwindow* window;
};

#endif