#include "InputHandler.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../Rendering/windowManager.h"
#include <glfw3.h>

InputHandler::InputHandler(GLFWwindow* window) : m_wireframeMode(false), m_wireframeKeyPressed(false), m_window(window) {}

void InputHandler::processInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_P) == GLFW_PRESS)
    {
        if (!m_wireframeKeyPressed)
        {
            m_wireframeKeyPressed = true;

            // Toggle wireframe mode
            m_wireframeMode = !m_wireframeMode;

            // Set polygon mode based on wireframeMode
            if (m_wireframeMode)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
    }
    else
    {
        m_wireframeKeyPressed = false;
    }
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        WindowManager::CaptureMouse(false);
    }
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) &&
            !ImGui::IsAnyItemHovered())
        {
            WindowManager::CaptureMouse(true);
        }
    }
}
