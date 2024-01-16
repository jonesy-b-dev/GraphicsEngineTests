#pragma once
#include "imgui_internal.h"
#include "windowManager.h"

class UserInterface
{
public:
	UserInterface(windowManager window);
	void NewFrame();
	void CreateSettingsWindow(ImVec4* clear_color, float* nearClip, float* farClip, float* fov);
	void RenderUI();
	void DestroyUI();
};

