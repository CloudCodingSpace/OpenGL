#include "Window.hpp"

Window::Window(int width, int height, const char* title)
{
    this->height = height;
    this->width = width;
    this->title = title;

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h){
		glViewport(0, 0, w, h);
	});
}

void Window::Cleanup()
{
    glfwDestroyWindow(window);
}

void Window::ProcessInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::ShowFPS()
{
	crntTime = glfwGetTime();
	timeDiff = crntTime - lstTime;
	counter++;
	if(timeDiff >= 1.0/15.0)
	{
		std::string FPS = std::to_string((1.0/timeDiff) * counter);
		glfwSetWindowTitle(window, (title + " | FPS :- " + FPS).c_str());
		lstTime = crntTime;
		counter = 0;
	}
}