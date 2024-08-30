#ifndef CAMERA_CLASS_HPP
#define CAMERA_CLASS_HPP

#include "../window/Window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shaders/Shader.hpp"

#include <math.h>

class Camera 
{
public:
    Camera(glm::vec3 pos, Window& window);
    void Update(Shader& shader);
    void Input();
    void PutMatrices(Shader& shader);
    glm::mat4 GetViewMat();
    glm::mat4 GetModelMat();
    glm::mat4 GetProjMat();
    glm::vec3 GetFront() { return front; }
    glm::vec3 GetUp() { return up; }
    glm::vec3 GetRight() { return right; }

    glm::vec3 pos, front, up, right;
    glm::mat4 view, proj, model;
    double crntX, crntY, lastX = 400, lastY = 300;
    float yaw = -90.0f, pitch = 0.0f, speed = 0.03f, sensitivity = 0.1f;
    Window& m_window;
    bool isCursorHidden = true, firstClick = true;
};

#endif