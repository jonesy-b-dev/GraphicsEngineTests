#pragma once

int main();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void printFps();

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 720;

double previousTime = glfwGetTime();
int frameCount = 0;

// Background color values 
ImVec4 clear_color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);