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
    void ShowFPS();

    GLFWwindow* window;
private:
    int width, height;
    std::string title;
    double crntTime = 0, lstTime = 0, timeDiff = 0;
    GLuint counter;
    bool isCursorHidden = true;
};

#endif