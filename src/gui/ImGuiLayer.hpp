#ifndef IMGUI_LAYER_HPP
#define IMGUI_LAYER_HPP

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class ImGuiLayer 
{
public:
    ImGuiLayer(GLFWwindow* window);
    void Render(void (*func)(void));
    void SendRenderData();
    void Cleanup();
};

#endif