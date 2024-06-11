#pragma once
#include "shader.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Renderer
{
public:
	static bool Initialise();
	static void CreateBuffers(float* vertices, size_t size);
	static void Render(Shader shaders, Shader lightShader, ImVec4* clear_color, float* nearClip, float* farClip, float* fov, float* aspectRatio, float* deltaTime, float* lastFrame, glm::vec3* cameraPos, glm::vec3* cameraFront, glm::vec3* cameraUp);
	static void Cleanup();
	// Create a array to store vertex data

	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 2,   // first triangle
	//	0, 2, 3    // second triangle
	//};

	// Create a var to store VBO, VAO and EBO ID
	static glm::vec3 lightPos;
	static unsigned int VBO, VAO, lightVAO, EBO;
};
