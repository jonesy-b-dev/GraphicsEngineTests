#include "InputHandler.h"
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
        glfwSetWindowShouldClose(m_window, true);
    }
}
