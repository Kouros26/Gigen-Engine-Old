#include "MenuBarDisplay.h"
#include "InterfaceManager.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Application.h"
#include "SceneSaver.h"
#include "Interface.h"

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
        if (ImGui::MenuItem("New Scene", "", false, true))
        {
            static char name[64];
            ImGui::InputText("Scene Name", name, sizeof(name));
            if (ImGui::Button("Create"))
            {
                Scene::GetInstance().SaveScene(std::string(name) + ".chad");
            }
        }
        if (ImGui::MenuItem("Save", "", false, true)) {}

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("test", "CTRL+Z")) {}
        if (ImGui::MenuItem("test2", "CTRL+X")) {}

        ImGui::EndMenu();
    }
    if (ImGui::Button(ICON_SAVE))
    {
        Scene::GetInstance().SaveScene(Scene::GetInstance().GetCurrentSceneName());
    }
    if (ImGui::BeginMenu("Themes"))
    {
        if (ImGui::MenuItem("Dark", "", false, true))
        {
            Interface::SetTheme(Theme::Dark);
        }
        if (ImGui::MenuItem("Light", "", false, true))
        {
            Interface::SetTheme(Theme::Light);
        }
        if (ImGui::MenuItem("Black", "", false, true))
        {
            Interface::SetTheme(Theme::Black);
        }
        if (ImGui::MenuItem("Classic", "", false, true))
        {
            Interface::SetTheme(Theme::Classic);
        }
        if (ImGui::MenuItem("Dracula", "", false, true))
        {
            Interface::SetTheme(Theme::Dracula);
        }
        if (ImGui::MenuItem("Cherry", "", false, true))
        {
            Interface::SetTheme(Theme::Cherry);
        }
        if (ImGui::MenuItem("Grey", "", false, true))
        {
            Interface::SetTheme(Theme::Grey);
        }
        if (ImGui::MenuItem("Blue", "", false, true))
        {
            Interface::SetTheme(Theme::Blue);
        }
        if (ImGui::MenuItem("ClassicDark", "", false, true))
        {
            Interface::SetTheme(Theme::ClassicDark);
        }
        if (ImGui::MenuItem("ClassicLight", "", false, true))
        {
            Interface::SetTheme(Theme::ClassicLight);
        }
        if (ImGui::MenuItem("Cinder", "", false, true))
        {
            Interface::SetTheme(Theme::Cinder);
        }

        ImGui::EndMenu();
    }

    DrawPlayPause();

    ImGui::EndMainMenuBar();
}

void MenuBarDisplay::DrawPlayPause() const
{
	ImGui::SameLine(ImGui::GetWindowContentRegionWidth() / 2 - 100);

	const bool isPause = Application::IsInPause();
	const bool isShowUI = Application::IsShowUI();
	const bool isPlaying = !Application::IsInEditor();
	const bool isUsingEditorCam = Application::IsUsingEditorCam();

    if (isPlaying)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, { 0,1,0,0.5f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0,1,0,0.6f });
    }

    if (ImGui::Button(ICON_PLAY, { 50, 0 }))
    {
        Application::Play();
    }

    if (isPlaying)
    {
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }

    if (isPause)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, { 0,1,0,0.5f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0,1,0,0.6f });
    }

    if (ImGui::Button(ICON_PAUSE, { 50, 0 }))
    {
        Application::Pause();
    }

    if (isPause)
    {
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }

    if (isUsingEditorCam)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, { 0,1,0,0.5f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0,1,0,0.6f });
    }

    if (ImGui::Button(ICON_CAMERA, { 50, 0 }))
    {
        Application::UseEditorCam();
    }

	if (isUsingEditorCam)
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	if (isShowUI)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, { 0,1,0,0.5f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0,1,0,0.6f });
	}

	if (ImGui::Button(ICON_TEXTURE " UI", { 50, 0 }))
	{
		Application::ShowUI();
	}

	if (isShowUI)
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}
}