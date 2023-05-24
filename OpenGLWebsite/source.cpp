#include "glad\glad.h"
#include <glfw3.h>
#include <iostream>
#include <stdio.h>

#include "source.h"
#include "errorHandeling.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.5f, 0.4f, 0.5f, 1.0f);\n"
"}\n\0";


int main()
{
	#pragma region Initialisation
	//Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core profile

	//Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLgamin", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	//Tell GLWF to call this function on every window resizes
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
#pragma endregion

	//Create a vertex shader object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Attach shader source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	errorHandeling::checkShader(vertexShader);

	//Create a vertex shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Attatch the shader and compile it	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	errorHandeling::checkShader(fragmentShader);

	//Create shader programm
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	errorHandeling::checkShaderProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Create a array to store vertex data
	float vertecies[] = {
		//x		y		z
		-0.5f, -0.5f, 0.0f, //Left
		 0.5f, -0.5f, 0.0f,	//Right
		 0.0f,  0.5f, 0.0f	//Top
	};

	//Create a vertex buffer object (VBO)
	unsigned int VBO;

	//Generates 1 id for the VBO and stores it in the VBO variable
	glGenBuffers(1, &VBO);

	//Copy the previous defined vertex data into the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Copy the vertex data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
	 
	//Vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//Main while render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//Render Commands
		glClearColor(0.5f, 0.4f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Swap frame buffers
		glfwSwapBuffers(window);
		//Check for any events
		glfwPollEvents();
	}

	//Clean up glfw 
	glfwTerminate();
    return 0;
} 

//Adjusts the window size when resolution is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


//Processes any key that is pressed
void processInput(GLFWwindow* window)
{
	//Print W to console for testing
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		std::cout << "W" << std::endl;
	}
}