#pragma once
#include "imgui_internal.h"
#include "windowManager.h"

class UserInterface
{
public:
	UserInterface(windowManager window);
	void NewFrame();
	void CreateWindows(ImVec4* clear_color, float* nearClip, float* farClip);
	void RenderUI();
	void DestroyUI();
};

