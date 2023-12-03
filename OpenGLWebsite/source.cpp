//includes all the libs
#include "source.h"
#include "shader.h"
#include "errorHandeling.h"
#include "InputHandler.h"
#include "windowManager.h"

int main()
{
	#pragma region Initialisation
	
	windowManager window(SCR_WIDTH, SCR_HEIGHT, "openglgaming");

	glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
	
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return -1;
	}
	//Print out OpenGL version to the console
	printf("%s\n", glGetString(GL_VERSION));

	//Create a input handler
	InputHandler inputHandler(window.getWindow());

	#pragma region ImGui Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
	#pragma endregion

#pragma endregion

	Shader shaders("vertexShader.vs", "fragmentShader.fs"); // you can name your shader files however you like

	#pragma region Buffer Stuff
	// Create a array to store vertex data
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		//1, 2, 3    // second triangle
	};

	// Create a var to store VBO, VAO and EBO ID
	unsigned int VBO, VAO, EBO;

	// Generates 1 id for the VBO and stores it in the VBO ID variable
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// Copy the previous defined vertex data into the buffer
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy the vertex data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	//                 index, size, type, normalized, stride,		pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	#pragma endregion


	#pragma region Main While Loop

	//Main while render loop
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		printFps();

		// Input
		inputHandler.processInput();

		// Render Commands
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		// ImGui stuff
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		shaders.use();

		//// Make trianle go sine with ts color
		//float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
		//glUniform4f(glGetUniformLocation(shaderProgram, "u_vertexColor"), 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		// Draw with EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		ImGui::Begin("TestWindow");
		ImGui::ColorEdit3("Background Color", (float*)&clear_color);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window.getWindow());
		// Check for any events
		glfwPollEvents();
	}
	#pragma endregion
	
	#pragma region Clean Up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Cleanup the resources when programm end
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//Clean up glfw 
	glfwTerminate();
	#pragma endregion
    
	return 0;
} 

#pragma region Additional Funcitons

//Adjusts the window size when resolution is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void printFps()
{
	double currentTime = glfwGetTime();
	frameCount++;
	// If a second has passed.
	if (currentTime - previousTime >= 1.0)
	{
		// Display the frame count here any way you want.
		printf("fps: ");
		printf("%d\n", frameCount);

		frameCount = 0;
		previousTime = currentTime;
	}
}
#pragma endregion