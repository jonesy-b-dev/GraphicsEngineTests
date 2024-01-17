#pragma once
#include "shader.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Renderer
{
public:
	bool Initialise();
	void CreateBuffers(float vertices[]);
	void Render(Shader shaders, ImVec4 clear_color, float nearClip, float farClip, float fov, float aspectRatio);
	void Cleanup();

	// Create a array to store vertex data

	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 2,   // first triangle
	//	0, 2, 3    // second triangle
	//};

	// Create a var to store VBO, VAO and EBO ID
	unsigned int VBO, VAO, EBO;
};
