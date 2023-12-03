#include "windowManager.h"
#include <stdio.h>

windowManager::windowManager(int width, int height, const char* name)
{
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
	

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);
}
