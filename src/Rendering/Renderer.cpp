#include "Renderer.h"
#include "windowManager.h"
#include "UserInterface.h"
#include "glad\glad.h"
#include "glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include <stdio.h>

// Initialize static members
unsigned int Renderer::VBO = 0;
unsigned int Renderer::VAO = 0;
unsigned int Renderer::EBO = 0;

bool Renderer::Initialise()
{
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return false;
	}
	//Print out OpenGL version to the console
	printf("%s\n", glGetString(GL_VERSION));

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
}

void Renderer::CreateBuffers(float* vertices, size_t size)
{
	// Generates 1 id for the VBO and stores it in the VBO ID variable
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// Copy the previous defined vertex data into the buffer

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy the vertex data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	//                 index, size, type, normalized, stride,        pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// Texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

void Renderer::Render(Shader shaders, ImVec4 clear_color, float nearClip, float farClip, float fov, float aspectRatio)
{
	// Render Commands
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
	
	// create transformations
		//glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	shaders.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shaders.setMat4("view", view);

	// render boxes
	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;

		if (i % 3 == 0)
			angle = glfwGetTime() * 25.0f;

		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shaders.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ImGui stuff
	UserInterface::NewFrame();

	UserInterface::CreateSettingsWindow(&clear_color, &nearClip, &farClip, &fov);

	UserInterface::RenderUI();

	glfwSwapBuffers(windowManager::getWindow());
	// Check for any events
	glfwPollEvents();
}

void Renderer::Cleanup()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
