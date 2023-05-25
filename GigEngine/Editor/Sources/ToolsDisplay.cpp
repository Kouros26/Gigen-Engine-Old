#include "ToolsDisplay.h"
#include "HierarchyDisplay.h"
#include "InterfaceManager.h"
#include "Console.h"
#include "imgui.h"

#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <stdlib.h>

ToolsDisplay::ToolsDisplay()
{
    InterfaceManager::AddEditorElement(this);
}

ToolsDisplay::~ToolsDisplay()
{
}

void ToolsDisplay::Draw()
{
    width = InterfaceManager::GetWidth() - InterfaceManager::GetClassWidth<HierarchyDisplay>();
    ImGui::SetNextWindowPos({ InterfaceManager::GetWidth() - width,  InterfaceManager::GetHeight() - height - g_menuBarSize });
    ImGui::SetNextWindowSize({ width, height });

    //noMove et NoCollapse
    ImGui::Begin("Tools", NULL, 4 | 32);

    LimitHeightResize();
    ImGui::SetWindowSize("Tools", { width, height });

    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("Explorer"))
        {
            DrawExplorer();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Console"))
        {
            DrawConsole();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Profiler"))
        {
            DrawProfiler();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void ToolsDisplay::DrawExplorer()
{
    fileExplorer.Draw();
}

void ToolsDisplay::DrawProfiler()
{
	fps.Draw();
}

void ToolsDisplay::DrawConsole()
{
    Console::Draw();
}