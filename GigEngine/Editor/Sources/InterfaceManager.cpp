#include "InterfaceManager.h"
#include "Application.h"
#include "GameObjectInspector.h"
#include "FileDisplay.h"
#include "HierarchyDisplay.h"

void InterfaceManager::DrawEditor()
{
    width = static_cast<float>(Application::GetWindow().GetWidth());
    height = static_cast<float>(Application::GetWindow().GetHeight()) - g_menuBarSize;

    for (const auto& displayable : displayables)
        displayable->Draw();

    const float posX = GetClassWidth<HierarchyDisplay>();
    const float posY = GetClassHeight<FileDisplay>();
    Application::GetWindow().SetViewPort(static_cast<int>(posX), static_cast<int>(posY), static_cast<int>(width - GetClassWidth<GameObjectInspector>() - posX), static_cast<int>(height - posY));
}

void InterfaceManager::AddEditorElement(Displayable* pElement)
{
    displayables.push_back(pElement);
}

void InterfaceManager::Cleanup()
{
    for (const auto& displayable : displayables)
        delete displayable;
}

float InterfaceManager::GetWidth()
{
    return width;
}

float InterfaceManager::GetHeight()
{
    return height;
}