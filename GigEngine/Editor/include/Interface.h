#pragma once
#include "FPSDisplay.h"
#include "ToolsDisplay.h"
#include "GameObjectInspector.h"
#include "HierarchyDisplay.h"
#include "MenuBarDisplay.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct GLFWwindow;

enum class Theme
{
    Dark,
    Light,
    Black,
    Classic,
    Dracula,
    Cherry,
    Grey,
    Blue,
    ClassicDark,
    ClassicLight,
    Cinder
};

class Interface
{
public:

    Interface(GLFWwindow* pWindow, const char* pGlslVersion);
    ~Interface();

    void BeginFrame();
    static void Draw();

    static void SetTheme(Theme pTheme);

private:

    void SetFont();

    GameObjectInspector gameObjInspector;
    HierarchyDisplay hierarchy;
    ToolsDisplay fileDisplay;
    MenuBarDisplay menuBar;
};