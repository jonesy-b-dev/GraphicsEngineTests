#include "windowManager.h"
#include <stdio.h>

// Initalise static members
float* WindowManager::m_aspectRatio = 0;
GLFWwindow* WindowManager::m_window = 0;
bool WindowManager::mouseCaptured = false;
Config_loader* WindowManager::m_config = nullptr;

// Private members
double WindowManager::previousTime = glfwGetTime();
int WindowManager::frameCount = 0;

bool WindowManager::InitWindow(int width, int height, std::string name, float* aspectRatio, Config_loader* config)
{
	m_aspectRatio = aspectRatio;
	m_config = config;
	
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
	m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (m_window == NULL)
	{
		printf("Failed to create GLFW window \n");
		glfwTerminate();
		return false;
	}

	WindowManager::CaptureMouse(true);

	glfwSetFramebufferSizeCallback(m_window, WindowManager::framebuffer_size_callback);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);
	return true;
}
void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	*m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	// Write new values to config
	m_config->WriteInt("window", "width", width);
	m_config->WriteInt("window", "height", height);

	glViewport(0, 0, width, height);
	//glfwSetWindowAspectRatio(window, width, height);
}

void WindowManager::printFps()
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
void WindowManager::CaptureMouse(bool capture)
{
	mouseCaptured = capture;
	glfwSetInputMode(m_window, GLFW_CURSOR, capture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void WindowManager::KillWindow()
{
	glfwTerminate();
	glfwDestroyWindow(m_window);
}
