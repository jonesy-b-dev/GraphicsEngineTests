#pragma once
#include "imgui_internal.h"
#include "windowManager.h"

class UserInterface
{
public:
	static void InitUI(GLFWwindow* window);
	static void NewFrame();
	static void CreateSettingsWindow(ImVec4* clear_color, float* nearClip, float* farClip, float* fov);
	static void RenderUI();
	static void DestroyUI();
};

