#include "windowManager.h"
#include <stdio.h>

// Initalise static members
float* windowManager::m_aspectRatio = 0;
GLFWwindow* windowManager::m_window = 0;

// Private members
double windowManager::previousTime = glfwGetTime();
int windowManager::frameCount = 0;

void windowManager::InitWindow(int width, int height, const char* name, float* aspectRatio)
{
	m_aspectRatio = aspectRatio;
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
	m_window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (m_window == NULL)
	{
		printf("Failed to create GLFW window \n");
		glfwTerminate();
		//return -1;
	}

	glfwSetFramebufferSizeCallback(m_window, windowManager::framebuffer_size_callback);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);
}
void windowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	*m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	glViewport(0, 0, width, height);
	//glfwSetWindowAspectRatio(window, width, height);
}

void windowManager::printFps()
{
	double currentTime = glfwGetTime();
	frameCount++;
	// If a second has passed.
	if (currentTime - previousTime >= 1.0)
	{
		// Convert frameCount to a string using sprintf_s
		char titleBuffer[256]; // Adjust the size as needed
		sprintf_s(titleBuffer, sizeof(titleBuffer), "fps: %d", frameCount);

		glfwSetWindowTitle(m_window, titleBuffer);

		frameCount = 0;
		previousTime = currentTime;
	}
}

void windowManager::KillWindow()
{
	glfwTerminate();
	glfwDestroyWindow(m_window);
}
