#ifndef WINDOW_CLASS_HPP
#define WINDOW_CLASS_HPP

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    void Cleanup();
    void ProcessInput();
    void Update();
    void ShowFPS();

    int GetWidth() { return width; }
    int GetHeight() { return height; }

    GLFWwindow* GetHandle() { return window; }
private:
    GLFWwindow* window;
    int width, height;
    std::string title;
    double crntTime = 0, lstTime = 0, timeDiff = 0;
    GLuint counter;
};

#endif