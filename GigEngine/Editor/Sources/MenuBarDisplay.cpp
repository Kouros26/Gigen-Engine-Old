#include "MenuBarDisplay.h"
#include "InterfaceManager.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Application.h"

MenuBarDisplay::MenuBarDisplay()
{
	InterfaceManager::AddEditorElement(this);
}

MenuBarDisplay::~MenuBarDisplay()
= default;

void MenuBarDisplay::Draw()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("test", "shortcut", false, true)) {}
		if (ImGui::MenuItem("test2", "truc", false, false)) {}

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("test", "CTRL+Z")) {}
		if (ImGui::MenuItem("test2", "CTRL+X")) {}

		ImGui::EndMenu();
	}

	DrawPlayPause();

	ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 40);
	if (ImGui::Button("Close"))
	{
		Application::GetWindow().Close();
	}

	ImGui::EndMainMenuBar();
}

void MenuBarDisplay::DrawPlayPause()
{
	ImGui::SameLine(ImGui::GetWindowContentRegionWidth() / 2 - 40);

	bool isPause = Application::IsInPause();
	bool isPlaying = !Application::IsInEditor();
	bool isUsingEditorCam = Application::IsUsingEditorCam();

	if (isPlaying)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if (ImGui::Button("Play"))
	{
		Application::Play();
	}

	if (isPlaying)
	{
		ImGui::PopStyleVar();
	}

	if (isPause)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if (ImGui::Button("Pause"))
	{
		Application::Pause();
	}

	if (isPause)
	{
		ImGui::PopStyleVar();
	}

	if (isUsingEditorCam)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if (ImGui::Button("Editor camera"))
	{
		Application::UseEditorCam();
	}

	if (isUsingEditorCam)
	{
		ImGui::PopStyleVar();
	}
}