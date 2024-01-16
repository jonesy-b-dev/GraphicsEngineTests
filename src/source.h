#pragma once
#define STB_IMAGE_IMPLEMENTATION

int main();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void printFps(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 1160;
unsigned int SCR_HEIGHT = 960;
static float nearClip = 0.1f;
static float farClip = 100.0f;
static float fieldOfView = 50.0f;
float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;


double previousTime = glfwGetTime();
int frameCount = 0;

// Background color values 
ImVec4 clear_color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);