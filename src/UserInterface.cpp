#include "UserInterface.h"
#include "imgui_internal.h"
#include "windowManager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

UserInterface::UserInterface(windowManager window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void UserInterface::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

}

void UserInterface::CreateWindows(ImVec4* clear_color, float* nearClip, float* farClip)
{
	ImGui::Begin("TestWindow");
	ImGui::ColorEdit3("Background Color", (float*)clear_color);
	ImGui::DragFloat("Near Clip plane", nearClip, 0.01f, 0.0f, 0.0f);
	ImGui::DragFloat("Far Clip plane", farClip, 0.01f, 0.0f, 0.0f);
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
