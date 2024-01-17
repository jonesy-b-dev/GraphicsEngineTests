#include "Renderer.h"
#include "glad\glad.h"
#include "glfw3.h"
#include <stdio.h>

bool Renderer::Initialise()
{
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return false;
	}
	//Print out OpenGL version to the console
	printf("%s\n", glGetString(GL_VERSION));

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
}

void Renderer::CreateBuffers()
{

}
