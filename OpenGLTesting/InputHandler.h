#pragma once
////////////////////////////////
// CALL AFTER WINDOW CREATION //
////////////////////////////////

#include <glfw3.h>

class InputHandler
{
private:
    bool m_wireframeMode;
    bool m_wireframeKeyPressed;
    GLFWwindow* m_window;

public:
    InputHandler(GLFWwindow* window);
    void processInput();
};


