#include "window/Window.hpp"
#include "shaders/Shader.hpp"
#include "mesh/TexturedMesh.hpp"
#include "mesh/ObjLoader.hpp"
#include "camera/Camera.hpp"
#include "gui/ImGuiLayer.hpp"
#include "texture/Skybox.hpp"

int main()
{
	std::vector<std::string> filePaths 
	{
		"./assets/skyboxes/Beach/posx.jpg",
		"./assets/skyboxes/Beach/negx.jpg",
		"./assets/skyboxes/Beach/posy.jpg",
		"./assets/skyboxes/Beach/negy.jpg",
		"./assets/skyboxes/Beach/posz.jpg",
		"./assets/skyboxes/Beach/negz.jpg"
	};
	// Creating required objects
	Window window(800, 600, "OpenGL!");
	Shader shader("./shaders/default.vert", "./shaders/default.frag");
	Mesh mesh = ObjLoader::loadMesh("./assets/objs/BossDragon.obj");
	Texture texture("./assets/textures/BossDragon.png", 1);
	TexturedMesh texturedMesh(mesh, texture, shader);
	Camera camera(glm::vec3(0, 10, -10), window);
	ImGuiLayer gui(window);
	Skybox skybox(filePaths);

	//Main loop
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glfwShowWindow(window.GetHandle());

	while (!glfwWindowShouldClose(window.GetHandle()))
	{
		window.ShowFPS();
		window.ProcessInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		glDisable(GL_CULL_FACE);
    	glDisable(GL_DEPTH_TEST);
		skybox.Render(camera);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);

		gui.Render([&]()
		{
			ImGui::Begin("Debug");
			ImGui::Text("Yay!");
			ImGui::End();
		});

		// Rendering the model
		camera.Update(shader);
		shader.PutMat4(glm::mat4(1.0f), "model"); 

		shader.PutVec3(glm::vec3(0.0f, 100.0f, -100.0f), "lightPos");
		shader.PutVec3(glm::vec3(1, 1, 1), "lightColor");
		shader.PutVec3(camera.pos, "cameraPos");
		shader.PutFloat(128, "shininess");

		texturedMesh.Render();
		
		// gui update stuff
		gui.SendRenderData();

		window.Update();
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