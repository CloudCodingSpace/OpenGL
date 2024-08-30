#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, Window& window)
        : m_window {window}
{
    this->pos = pos;
    this->m_window = window;
    this->view = glm::mat4(1.0f);

    up = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
}

void Camera::Update(Shader& shader)
{
    Input();
    PutMatrices(shader);
}

void Camera::Input()
{
    GLFWwindow* window = m_window.GetHandle();

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
    if(glfwGetMouseButton(m_window.GetHandle(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(m_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        isCursorHidden = true;

        if(firstClick) {
            firstClick = false;
            return;
        }

        glfwGetCursorPos(window, &crntX, &crntY);
        float xoffset = crntX - lastX;
        float yoffset = lastY - crntY;
        lastX = crntX;
        lastY = crntY;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(pitch < -90.0f)
            pitch = 89.0f;
        if(pitch > 90.0f)
            pitch = -89.0f;

        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
        up = glm::normalize(glm::cross(right, front));
    } 
    if((glfwGetMouseButton(m_window.GetHandle(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) && isCursorHidden) {
        glfwSetCursorPos(m_window.GetHandle(), m_window.GetWidth()/2, m_window.GetHeight()/2);
        glfwSetInputMode(m_window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        firstClick = true;
        isCursorHidden = false;
    }
}

void Camera::PutMatrices(Shader& shader)
{
    view = glm::mat4(1.0f);
    view = lookAt(pos, pos + front, up);

    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(90.0f), (float)m_window.GetWidth()/(float)m_window.GetHeight(), 0.1f, 1000.0f);

    shader.PutMat4(view, "view");
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
