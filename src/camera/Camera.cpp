#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, GLFWwindow* window)
{
    this->pos = pos;
    this->window = window;
    this->view = glm::mat4(1.0f);

    up = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera::Update(Shader& shader)
{
    Input();
    PutMatrices(shader);
}

void Camera::Input()
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += front * speed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= front * speed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(front, up)) * speed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += glm::normalize(glm::cross(front, up)) * speed;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        pos += up * speed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pos -= up * speed;

    //Mouse Input or Mouse pos change callback
    glfwGetCursorPos(window, &crntX, &crntY);
    float xoffset = crntX - lastX;
    float yoffset = lastY - crntY;
    lastX = crntX;
    lastY = crntY;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch < -89.9999999999999999999999999f)
        pitch = 89.0f;
    if(pitch > 89.9999999999999999999999999f)
        pitch = -89.0f;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}

void Camera::PutMatrices(Shader &shader)
{
    view = glm::mat4(1.0f);
    view = lookAt(pos, pos + front, up);

    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(90.0f), 800.0f/600.0f, 0.1f, 1000.0f);

    model = glm::mat4(1.0f);

    shader.PutMat4(view, "view");
    shader.PutMat4(model, "model");
    shader.PutMat4(proj, "proj");
}

glm::mat4 Camera::GetViewMat()
{
    return view;
}

glm::mat4 Camera::GetModelMat()
{
    return model;
}

glm::mat4 Camera::GetProjMat()
{
    return proj;
}
