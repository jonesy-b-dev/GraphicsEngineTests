#include "UserInterface.h"
#include "imgui_internal.h"
#include "windowManager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glfw3.h>

void UserInterface::InitUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void UserInterface::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

}

void UserInterface::CreateSettingsWindow(ImVec4* clear_color, float* nearClip, float* farClip, float* fov)
{
	ImGui::Begin("TestWindow");
	ImGui::ColorEdit3("Background Color", (float*)clear_color);
	ImGui::DragFloat("Near Clip plane", nearClip, 0.01f, 0.0001f, 1000000000);
	ImGui::DragFloat("Far Clip plane", farClip, 0.01f, 0.0001f, 1000000000);
	ImGui::DragFloat("Field of view", fov, 0.1f, -1000.0f, 1000.0f,"%.01f deg");
	ImGui::End();
}

void UserInterface::RenderUI()
{
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::DestroyUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
