#include "glad\glad.h"
#include <glfw3.h>
#include <stdio.h>
#include <cmath>
#include "source.h"
#include "errorHandeling.h"

#pragma region Shader Code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 u_vertexColor;\n"
"void main()\n"
"{\n"
"	FragColor = u_vertexColor;\n"
"}\n\0";
#pragma endregion


int main()
{
	#pragma region Initialisation
	//Init GLFW
    glfwInit();
	// uncomment for (borderless) fullscreen mode 
	//GLFWmonitor* primary = glfwGetPrimaryMonitor(); 
	//const GLFWvidmode* mode = glfwGetVideoMode(primary);
	//
	//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	//
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core profile
	//Create window
	//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenGLgamin", primary, NULL);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLgamin", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window \n");
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	//Tell GLWF to call this function on every window resizes
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return -1;
	}
#pragma endregion

	#pragma region Shader Stuff
	// Create a vertex shader object
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach shader source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	errorHandeling::checkShader(vertexShader);

	// Create a fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Attatch the shader and compile it	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	errorHandeling::checkShader(fragmentShader);

	// Create shader programm
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	errorHandeling::checkShaderProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	#pragma endregion

	#pragma region Buffer Stuff
	// Create a array to store vertex data
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// Create a var to store VBO, VAO and EBO ID
	unsigned int VBO, VAO, EBO;

	// Generates 1 id for the VBO and stores it in the VBO ID variable
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// Copy the previous defined vertex data into the buffer
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy the vertex data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	#pragma endregion

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

#pragma region Main While Loop
	//Main while render loop
	while (!glfwWindowShouldClose(window))
	{
		printFps();

		// Input
		processInput(window);

		// Render Commands
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program we created earlier
		glUseProgram(shaderProgram);

		// Make trianle go sine with ts color
		float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
		glUniform4f(glGetUniformLocation(shaderProgram, "u_vertexColor"), 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		// Draw with EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Check for any events
		glfwPollEvents();
	}
	#pragma endregion
	
	#pragma region Clean Up
	// Cleanup the resources when programm end
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	#pragma endregion

	//Clean up glfw 
	glfwTerminate();
    return 0;
} 

//Adjusts the window size when resolution is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}



void printFps()
{
	double currentTime = glfwGetTime();
	frameCount++;
	// If a second has passed.
	if (currentTime - previousTime >= 1.0)
	{
		// Display the frame count here any way you want.
		printf("fps: ");
		printf("%d\n", frameCount);

		frameCount = 0;
		previousTime = currentTime;
	}
}
#pragma region Input
bool wireframeMode = false;
bool wireframeKeyPressed = false;


//Processes any key that is pressed
void processInput(GLFWwindow* window)
{
	// Toggle between wireframe mode and fill mode
	// In your rendering loop:
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		// Set the flag to true only if it wasn't already set
		if (!wireframeKeyPressed)
		{
			wireframeKeyPressed = true;

			// Toggle between wireframe mode and normal mode
			if (wireframeMode)
			{
				wireframeMode = false;
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				wireframeMode = true;
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	}
	else
	{
		// Reset the flag when the key is released
		wireframeKeyPressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
#pragma endregion