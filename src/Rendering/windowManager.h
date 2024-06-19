#pragma once
#include <string>
#include <glfw3.h>
#include "../Utils/config_loader.h"

class WindowManager
{
public:
	static float* m_aspectRatio;
	static bool mouseCaptured;

	static bool InitWindow(int width, int height, std::string name, float* aspectRatio, Config_loader* config);
	static GLFWwindow* GetWindow() { return m_window; }
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void KillWindow();
	static void printFps();
	static void CaptureMouse(bool capture);

private:
	static double previousTime;
	static int frameCount;
	static GLFWwindow* m_window;
	static Config_loader* m_config;
};