#include "Window.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "TexturedMesh.hpp"
#include "ObjLoader.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"
#include "ImGuiLayer.hpp"

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
	Mesh mesh = ObjLoader::loadMesh("./assets/objs/Cube.obj");
	Texture texture("./assets/textures/white.jpg", 1);
	TexturedMesh texturedMesh(mesh, texture, shader);
	Camera camera(glm::vec3(0, 10, -10), window.window);
	ImGuiLayer gui(window.window);
	Skybox skybox(filePaths);

	glm::mat4 model(1.0f);
	glm::mat4 proj(1.0f);

	//Main loop
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


			if(ImGui::BeginMainMenuBar())
			{
				if(ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("New", "Ctrl + N");
					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}
		});

		// Rendering the model
		proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(90.0f), 800.0f/600.0f, 0.1f, 1000.0f);
		model = glm::mat4(1.0f);

		camera.Input();
		
		shader.PutMat4(proj, "proj");
		shader.PutMat4(model, "model");
		camera.PutMatrices(shader);

		shader.PutVec3(glm::vec3(0.0f, 100.0f, -100.0f), "lightPos");
		shader.PutVec3(glm::vec3(1, 1, 1), "lightColor");
		shader.PutVec3(camera.pos, "cameraPos");
		shader.PutFloat(128, "shininess");

		texturedMesh.Render();

		skybox.Render(camera.GetViewMat(), proj);
		
		gui.SendRenderData();

		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}

	//Cleaning up resources
	skybox.Cleanup();
	window.Cleanup();
	gui.Cleanup();
	texturedMesh.Cleanup();
	shader.Cleanup();

	glfwTerminate();
	return 0;
}