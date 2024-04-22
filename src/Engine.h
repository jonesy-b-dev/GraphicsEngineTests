#pragma once
#define STB_IMAGE_IMPLEMENTATION

// settings
unsigned int SCR_WIDTH = 1160;
unsigned int SCR_HEIGHT = 860;
float nearClip = 0.1f;
float farClip = 100.0f;
float fieldOfView = 50.0f;
float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;

struct WindowSettings
{
	unsigned int screenWidth = 1160;
	unsigned int screenHeight = 860;
};

struct CameraSettings
{

};

// Background color values 
ImVec4 clear_color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);