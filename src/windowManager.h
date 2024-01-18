#pragma once
#include <glfw3.h>
class windowManager
{
public:
	static float* m_aspectRatio;

	windowManager(int width, int height, const char* name, float* aspectRatio);
	GLFWwindow* m_window;
	GLFWwindow* getWindow() { return m_window; }
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
	void KillWindow();
};

