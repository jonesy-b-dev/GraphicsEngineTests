#pragma once
#include <glfw3.h>
class windowManager
{
public:
	windowManager(int width, int height, const char* name);

	GLFWwindow* m_window;
	GLFWwindow* getWindow() { return m_window; }
};

