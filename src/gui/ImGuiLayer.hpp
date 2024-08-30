#ifndef IMGUI_LAYER_HPP
#define IMGUI_LAYER_HPP

#include "../window/Window.hpp"

#include <functional>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class ImGuiLayer 
{
public:
    ImGuiLayer(Window& window);
    void Render(std::function<void(void)> func);
    void SendRenderData();
    void Cleanup();
};

#endif