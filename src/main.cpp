#include "window/Window.hpp"
#include "shaders/Shader.hpp"
#include "mesh/TexturedMesh.hpp"
#include "mesh/ObjLoader.hpp"
#include "camera/Camera.hpp"
#include "gui/ImGuiLayer.hpp"

int main()
{
	std::vector<std::string> filePaths 
	{
		"./assets/skyboxes/IcyLakeView/right.jpg",
		"./assets/skyboxes/IcyLakeView/left.jpg",
		"./assets/skyboxes/IcyLakeView/top.jpg",
		"./assets/skyboxes/IcyLakeView/bottom.jpg",
		"./assets/skyboxes/IcyLakeView/front.jpg",
		"./assets/skyboxes/IcyLakeView/back.jpg"
	};
	// Creating required objects
	Window window(800, 600, "OpenGL!");
	Shader shader("./shaders/default.vert", "./shaders/default.frag");
	Mesh mesh = ObjLoader::loadMesh("./assets/objs/BossDragon.obj");
	Texture texture("./assets/textures/BossDragon.png", 1);
	TexturedMesh texturedMesh(mesh, texture, shader);
	Camera camera(glm::vec3(0, 10, -10), window.window);
	ImGuiLayer gui(window.window);

	//Main loop
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glfwShowWindow(window.window);
	while (!glfwWindowShouldClose(window.window))
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		window.ShowFPS();
		window.ProcessInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gui.Render([]()
		{
			ImGui::Begin("Debug");
			ImGui::Text("Yay!");
			ImGui::End();
		});

		// Rendering the model
		camera.Update(shader);

		shader.PutVec3(glm::vec3(0.0f, 100.0f, -100.0f), "lightPos");
		shader.PutVec3(glm::vec3(1, 1, 1), "lightColor");
		shader.PutVec3(camera.pos, "cameraPos");
		shader.PutFloat(128, "shininess");

		texturedMesh.Render();
		
		gui.SendRenderData();

		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}

	//Cleaning up resources
	window.Cleanup();
	gui.Cleanup();
	texturedMesh.Cleanup();
	shader.Cleanup();

	glfwTerminate();
	return 0;
}