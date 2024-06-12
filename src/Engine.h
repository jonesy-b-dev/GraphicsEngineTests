#pragma once
#define STB_IMAGE_IMPLEMENTATION

// settings
unsigned int SCR_WIDTH = 1160;
unsigned int SCR_HEIGHT = 860;
float nearClip = 0.1f;
float farClip = 100.0f;
float fieldOfView = 50.0f;
float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


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