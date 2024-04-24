#pragma once
#include <glfw3.h>

class WindowManager
{
public:
	static float* m_aspectRatio;
	static GLFWwindow* m_window;

	static void InitWindow(int width, int height, const char* name, float* aspectRatio);
	static GLFWwindow* getWindow() { return m_window; }
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void KillWindow();
	static void printFps();
	static void CaptureMouse(bool capture);

private:
	static double previousTime;
	static int frameCount;

};