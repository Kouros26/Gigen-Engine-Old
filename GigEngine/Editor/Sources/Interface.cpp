#include "Interface.h"
#include "InterfaceManager.h"
#include "IconsMaterialDesignIcons.h"
#include <imgui_impl_opengl3.h>
#include "imgui_impl_glfw.h"
#include <imgui/imgui_internal.h>

Interface::Interface(GLFWwindow* pWindow, const char* pGlslVersion)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
    ImGui_ImplOpenGL3_Init(pGlslVersion);
    ImGui::StyleColorsDark();
    ImGui::GetStyle().FrameRounding = 5;
    ImGui::GetStyle().WindowBorderSize = 0.0f;
    SetTheme(Theme::Black);
    SetFont();
}

Interface::~Interface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Interface::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Interface::Draw()
{
    InterfaceManager::DrawEditor();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::SetTheme(Theme pTheme)
{
    static const float max = 255.0f;

    auto& style = ImGui::GetStyle();
    ImVec4* colours = style.Colors;

    if (pTheme == Theme::Black)
    {
        colours[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colours[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colours[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colours[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colours[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colours[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colours[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colours[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colours[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colours[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colours[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colours[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colours[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colours[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colours[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colours[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colours[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colours[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colours[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colours[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colours[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colours[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colours[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colours[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colours[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colours[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colours[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colours[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colours[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colours[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colours[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        colours[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }
    else if (pTheme == Theme::Dark)
    {
        ImGui::StyleColorsDark();
        ImVec4 Titlebar = ImVec4(40.0f / max, 42.0f / max, 54.0f / max, 1.0f);
        ImVec4 TabActive = ImVec4(52.0f / max, 54.0f / max, 64.0f / max, 1.0f);
        ImVec4 TabUnactive = ImVec4(35.0f / max, 43.0f / max, 59.0f / max, 1.0f);
        colours[ImGuiCol_Text] = ImVec4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);

        colours[ImGuiCol_WindowBg] = TabActive;
        colours[ImGuiCol_ChildBg] = TabActive;

        colours[ImGuiCol_PopupBg] = ImVec4(42.0f / 255.0f, 38.0f / 255.0f, 47.0f / 255.0f, 1.00f);
        colours[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colours[ImGuiCol_FrameBg] = ImVec4(65.0f / 255.0f, 79.0f / 255.0f, 92.0f / 255.0f, 1.00f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);

        colours[ImGuiCol_TitleBg] = Titlebar;
        colours[ImGuiCol_TitleBgActive] = Titlebar;
        colours[ImGuiCol_TitleBgCollapsed] = Titlebar;
        colours[ImGuiCol_MenuBarBg] = Titlebar;

        colours[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.7f, 0.7f, 0.7f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);

        colours[ImGuiCol_CheckMark] = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(185.0f / 255.0f, 160.0f / 255.0f, 237.0f / 255.0f, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(0.2f + 0.1f, 0.25f + 0.1f, 0.29f + 0.1f, 1.00f + 0.1f);
        colours[ImGuiCol_ButtonActive] = ImVec4(0.2f + 0.1f, 0.25f + 0.1f, 0.29f + 0.1f, 1.00f + 0.1f);

        colours[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colours[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colours[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

        colours[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

        colours[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colours[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colours[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colours[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        colours[ImGuiCol_Header] =
            colours[ImGuiCol_HeaderHovered] = ImVec4(0.1f + TabActive.x, 0.1f + TabActive.y, 0.1f + TabActive.z, 0.1f + TabActive.w);
        colours[ImGuiCol_HeaderActive] = ImVec4(0.55f + TabActive.x, 0.55f + TabActive.y, 0.55f + TabActive.z, 0.1f + TabActive.w);

#ifdef IMGUI_HAS_DOCK

        colours[ImGuiCol_Tab] = TabUnactive;
        colours[ImGuiCol_TabHovered] = TabActive + ImVec4(0.1f, 0.1f, 0.1f, 0.1f);
        colours[ImGuiCol_TabActive] = TabActive;
        colours[ImGuiCol_TabUnfocused] = TabUnactive;
        colours[ImGuiCol_TabUnfocusedActive] = TabActive;
        colours[ImGuiCol_DockingEmptyBg] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
        colours[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);

#endif
    }
    else if (pTheme == Theme::Grey)
    {
        ImGui::StyleColorsDark();
        colours[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

        colours[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colours[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colours[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colours[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
        colours[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colours[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
        colours[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
        colours[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        colours[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
        colours[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
        colours[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
        colours[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
        colours[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
        colours[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        colours[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
        colours[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
        colours[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
        colours[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
        colours[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
        colours[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colours[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
        colours[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        colours[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colours[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colours[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

#ifdef IMGUI_HAS_DOCK
        colours[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        colours[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colours[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        colours[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
        colours[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
        colours[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);
#endif
    }
    else if (pTheme == Theme::Light)
    {
        ImGui::StyleColorsLight();
        colours[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);

        colours[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
        colours[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        colours[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
        colours[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
        colours[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colours[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
        colours[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        colours[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
        colours[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        colours[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        colours[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colours[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        colours[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colours[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colours[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    }
    else if (pTheme == Theme::Cherry)
    {
        ImGui::StyleColorsDark();
#define HI(v) ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v) ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v) ImVec4(0.232f, 0.201f, 0.271f, v)
#define BG(v) ImVec4(0.200f, 0.220f, 0.270f, v)
#define TEXTCol(v) ImVec4(0.860f, 0.930f, 0.890f, v)

        colours[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);

        colours[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
        colours[ImGuiCol_PopupBg] = BG(0.9f);
        colours[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
        colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colours[ImGuiCol_FrameBg] = BG(1.00f);
        colours[ImGuiCol_FrameBgHovered] = MED(0.78f);
        colours[ImGuiCol_FrameBgActive] = MED(1.00f);
        colours[ImGuiCol_TitleBg] = LOW(1.00f);
        colours[ImGuiCol_TitleBgActive] = HI(1.00f);
        colours[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
        colours[ImGuiCol_MenuBarBg] = BG(0.47f);
        colours[ImGuiCol_ScrollbarBg] = BG(1.00f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
        colours[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
        colours[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        colours[ImGuiCol_ButtonHovered] = MED(0.86f);
        colours[ImGuiCol_ButtonActive] = MED(1.00f);
        colours[ImGuiCol_Header] = MED(0.76f);
        colours[ImGuiCol_HeaderHovered] = MED(0.86f);
        colours[ImGuiCol_HeaderActive] = HI(1.00f);
        colours[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
        colours[ImGuiCol_ResizeGripHovered] = MED(0.78f);
        colours[ImGuiCol_ResizeGripActive] = MED(1.00f);
        colours[ImGuiCol_PlotLines] = TEXTCol(0.63f);
        colours[ImGuiCol_PlotLinesHovered] = MED(1.00f);
        colours[ImGuiCol_PlotHistogram] = TEXTCol(0.63f);
        colours[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
        colours[ImGuiCol_TextSelectedBg] = MED(0.43f);
        colours[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
        colours[ImGuiCol_TabHovered] = colours[ImGuiCol_ButtonHovered];
    }
    else if (pTheme == Theme::Blue)
    {
        ImVec4 colour_for_text = ImVec4(236.f / 255.f, 240.f / 255.f, 241.f / 255.f, 1.0f);
        ImVec4 colour_for_head = ImVec4(41.f / 255.f, 128.f / 255.f, 185.f / 255.f, 1.0f);
        ImVec4 colour_for_area = ImVec4(57.f / 255.f, 79.f / 255.f, 105.f / 255.f, 1.0f);
        ImVec4 colour_for_body = ImVec4(44.f / 255.f, 62.f / 255.f, 80.f / 255.f, 1.0f);
        ImVec4 colour_for_pops = ImVec4(33.f / 255.f, 46.f / 255.f, 60.f / 255.f, 1.0f);
        colours[ImGuiCol_Text] = ImVec4(colour_for_text.x, colour_for_text.y, colour_for_text.z, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(colour_for_text.x, colour_for_text.y, colour_for_text.z, 0.58f);

        colours[ImGuiCol_WindowBg] = ImVec4(colour_for_body.x, colour_for_body.y, colour_for_body.z, 0.95f);
        colours[ImGuiCol_Border] = ImVec4(colour_for_body.x, colour_for_body.y, colour_for_body.z, 0.00f);
        colours[ImGuiCol_BorderShadow] = ImVec4(colour_for_body.x, colour_for_body.y, colour_for_body.z, 0.00f);
        colours[ImGuiCol_FrameBg] = ImVec4(colour_for_area.x, colour_for_area.y, colour_for_area.z, 1.00f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.78f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_TitleBg] = ImVec4(colour_for_area.x, colour_for_area.y, colour_for_area.z, 1.00f);
        colours[ImGuiCol_TitleBgCollapsed] = ImVec4(colour_for_area.x, colour_for_area.y, colour_for_area.z, 0.75f);
        colours[ImGuiCol_TitleBgActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_MenuBarBg] = ImVec4(colour_for_area.x, colour_for_area.y, colour_for_area.z, 0.47f);
        colours[ImGuiCol_ScrollbarBg] = ImVec4(colour_for_area.x, colour_for_area.y, colour_for_area.z, 1.00f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.21f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.78f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_CheckMark] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.80f);
        colours[ImGuiCol_SliderGrab] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.50f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.50f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.86f);
        colours[ImGuiCol_ButtonActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_Header] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.76f);
        colours[ImGuiCol_HeaderHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.86f);
        colours[ImGuiCol_HeaderActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_ResizeGrip] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.15f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.78f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_PlotLines] = ImVec4(colour_for_text.x, colour_for_text.y, colour_for_text.z, 0.63f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(colour_for_text.x, colour_for_text.y, colour_for_text.z, 0.63f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 1.00f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(colour_for_head.x, colour_for_head.y, colour_for_head.z, 0.43f);
        colours[ImGuiCol_PopupBg] = ImVec4(colour_for_pops.x, colour_for_pops.y, colour_for_pops.z, 0.92f);
    }
    else if (pTheme == Theme::Classic)
    {
        ImGui::StyleColorsClassic();
    }
    else if (pTheme == Theme::ClassicDark)
    {
        ImGui::StyleColorsDark();
    }
    else if (pTheme == Theme::ClassicLight)
    {
        ImGui::StyleColorsLight();
    }
    else if (pTheme == Theme::Cinder)
    {
        colours[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);

        colours[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
        colours[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
        colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colours[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_TitleBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
        colours[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
        colours[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_MenuBarBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
        colours[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
        colours[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
        colours[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
        colours[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
        colours[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
    }
    else if (pTheme == Theme::Dracula)
    {
        ImGui::StyleColorsDark();

        ImVec4 Titlebar = ImVec4(33.0f / max, 34.0f / max, 44.0f / max, 1.0f);
        ImVec4 TabActive = ImVec4(40.0f / max, 42.0f / max, 54.0f / max, 1.0f);
        ImVec4 TabUnactive = ImVec4(35.0f / max, 43.0f / max, 59.0f / max, 1.0f);
        colours[ImGuiCol_Text] = ImVec4(244.0f / 255.0f, 244.0f / 255.0f, 244.0f / 255.0f, 1.00f);
        colours[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);

        colours[ImGuiCol_WindowBg] = TabActive;
        colours[ImGuiCol_ChildBg] = TabActive;

        colours[ImGuiCol_PopupBg] = ImVec4(42.0f / 255.0f, 38.0f / 255.0f, 47.0f / 255.0f, 1.00f);
        colours[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colours[ImGuiCol_FrameBg] = ImVec4(65.0f / 255.0f, 79.0f / 255.0f, 92.0f / 255.0f, 1.00f);
        colours[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colours[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);

        colours[ImGuiCol_TitleBg] = Titlebar;
        colours[ImGuiCol_TitleBgActive] = Titlebar;
        colours[ImGuiCol_TitleBgCollapsed] = Titlebar;
        colours[ImGuiCol_MenuBarBg] = Titlebar;

        colours[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.7f, 0.7f, 0.7f, 1.00f);
        colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);

        colours[ImGuiCol_CheckMark] = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
        colours[ImGuiCol_SliderGrab] = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
        colours[ImGuiCol_SliderGrabActive] = ImVec4(185.0f / 255.0f, 160.0f / 255.0f, 237.0f / 255.0f, 1.00f);
        colours[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colours[ImGuiCol_ButtonHovered] = ImVec4(59.0f / 255.0f, 46.0f / 255.0f, 80.0f / 255.0f, 1.0f);
        colours[ImGuiCol_ButtonActive] = ImVec4(0.1f + colours[ImGuiCol_ButtonHovered].x, 0.1f + colours[ImGuiCol_ButtonHovered].y, 0.1f + colours[ImGuiCol_ButtonHovered].z, 0.1f + colours[ImGuiCol_ButtonHovered].w);

        colours[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colours[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colours[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

        colours[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colours[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

        colours[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colours[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colours[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colours[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colours[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colours[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colours[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colours[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colours[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        colours[ImGuiCol_Header] = ImVec4(0.1f + TabActive.x, 0.1f + TabActive.y, 0.1f + TabActive.z, 0.1f + TabActive.w);
        colours[ImGuiCol_HeaderHovered] = ImVec4(0.1f + TabActive.x, 0.1f + TabActive.y, 0.1f + TabActive.z, 0.1f + TabActive.w);
        colours[ImGuiCol_HeaderActive] = ImVec4(0.05f + TabActive.x, 0.05f + TabActive.y, 0.05f + TabActive.z, 0.1f + TabActive.w);

#ifdef IMGUI_HAS_DOCK

        colours[ImGuiCol_Tab] = TabUnactive;
        colours[ImGuiCol_TabHovered] = TabActive + ImVec4(0.1f, 0.1f, 0.1f, 0.1f);
        colours[ImGuiCol_TabActive] = TabActive;
        colours[ImGuiCol_TabUnfocused] = TabUnactive;
        colours[ImGuiCol_TabUnfocusedActive] = TabActive;
        colours[ImGuiCol_DockingEmptyBg] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
        colours[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);

#endif
    }

    colours[ImGuiCol_Separator] = colours[ImGuiCol_TitleBg];
    colours[ImGuiCol_SeparatorActive] = colours[ImGuiCol_Separator];
    colours[ImGuiCol_SeparatorHovered] = colours[ImGuiCol_Separator];

    colours[ImGuiCol_Tab] = colours[ImGuiCol_MenuBarBg];
    colours[ImGuiCol_TabUnfocused] = colours[ImGuiCol_MenuBarBg];

    colours[ImGuiCol_TabUnfocusedActive] = colours[ImGuiCol_WindowBg];
    colours[ImGuiCol_TabActive] = colours[ImGuiCol_WindowBg];
    colours[ImGuiCol_ChildBg] = colours[ImGuiCol_TabActive];
    colours[ImGuiCol_ScrollbarBg] = colours[ImGuiCol_TabActive];

    colours[ImGuiCol_TitleBgActive] = colours[ImGuiCol_TitleBg];
    colours[ImGuiCol_TitleBgCollapsed] = colours[ImGuiCol_TitleBg];
    colours[ImGuiCol_MenuBarBg] = colours[ImGuiCol_TitleBg];
    colours[ImGuiCol_PopupBg] = ImVec4(0.05f + colours[ImGuiCol_WindowBg].x, 0.05f + colours[ImGuiCol_WindowBg].y, 0.05f + colours[ImGuiCol_WindowBg].z, 0.0f + colours[ImGuiCol_WindowBg].w);

    colours[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 0.00f);
    colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
}

void Interface::SetFont()
{
    ImGuiIO& io = ImGui::GetIO();
    io.FontDefault = io.Fonts->AddFontFromFileTTF("Engine/Fonts/Ruda-Bold.ttf", 16.0f);

    ImFontConfig config;
    config.MergeMode = true;
    config.PixelSnapH = true;
    config.OversampleH = config.OversampleV = 1;
    config.GlyphMinAdvanceX = 4.0f;
    config.SizePixels = 12.0f;

    static const ImWchar icon_ranges[] = { ICON_MIN_MD, (ImWchar)ICON_MAX_MD, 0 };

    io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_MD, 12.0f, &config, icon_ranges);
    io.Fonts->TexGlyphPadding = 1;
    for (int n = 0; n < io.Fonts->ConfigData.Size; n++)
    {
        ImFontConfig* font_config = (ImFontConfig*)&io.Fonts->ConfigData[n];
        font_config->RasterizerMultiply = 1.0f;
    }
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(5, 5);
    style.FramePadding = ImVec2(4, 4);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(2, 2);
    style.IndentSpacing = 6.0f;
    style.TouchExtraPadding = ImVec2(4, 4);

    style.ScrollbarSize = 10;

    style.WindowBorderSize = 0;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 3;
    style.FrameBorderSize = 0.0f;

    const int roundingAmount = 2;
    style.PopupRounding = roundingAmount;
    style.WindowRounding = roundingAmount;
    style.ChildRounding = 0;
    style.FrameRounding = roundingAmount;
    style.ScrollbarRounding = roundingAmount;
    style.GrabRounding = roundingAmount;
    style.WindowMinSize = ImVec2(200.0f, 200.0f);
    /* ImFontConfig config;
    config.MergeMode = false;
    config.PixelSnapH = true;
    config.OversampleH = config.OversampleV = 1;
    config.GlyphMinAdvanceX = 4.0f;
    config.SizePixels = 12.0f;

    static const ImWchar icon_ranges[] = { ICON_MIN_MD, (ImWchar)ICON_MAX_MD, 0 };

    io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_MD, 12.0f, &config, icon_ranges);
    io.Fonts->TexGlyphPadding = 1;
    for (int n = 0; n < io.Fonts->ConfigData.Size; n++)
    {
        ImFontConfig* font_config = (ImFontConfig*)&io.Fonts->ConfigData[n];
        font_config->RasterizerMultiply = 1.0f;
    }
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(5, 5);
    style.FramePadding = ImVec2(4, 4);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(2, 2);
    style.IndentSpacing = 6.0f;
    style.TouchExtraPadding = ImVec2(4, 4);

    style.ScrollbarSize = 10;

    style.WindowBorderSize = 0;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 3;
    style.FrameBorderSize = 0.0f;

    const int roundingAmount = 2;
    style.PopupRounding = roundingAmount;
    style.WindowRounding = roundingAmount;
    style.ChildRounding = 0;
    style.FrameRounding = roundingAmount;
    style.ScrollbarRounding = roundingAmount;
    style.GrabRounding = roundingAmount;
    style.WindowMinSize = ImVec2(200.0f, 200.0f);*/
}