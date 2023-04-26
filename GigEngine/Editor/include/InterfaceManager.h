#pragma once
#include <vector>
#include "Displayable.h"

constexpr float g_basicSize = 300;
constexpr float g_menuBarSize = 20;

constexpr float g_maxStep = 0.1f;
const char* const g_floatFormat = "%.2f";
constexpr float g_floatMin = -1000000.0f;
constexpr float g_floatMax = 1000000.0f;

class InterfaceManager
{
public:

    static void DrawEditor();
    static void AddEditorElement(Displayable* pElement);
    static void Cleanup();

    static float GetWidth();
    static float GetHeight();

    template< typename T>
    static float GetClassHeight();

    template< typename T>
    static float GetClassWidth();

private:

    inline static std::vector<Displayable*> displayables{};
    inline static float width;
    inline static float height;
};

template<typename T>
inline float InterfaceManager::GetClassHeight()
{
    for (auto displayable : displayables)
    {
	    if (T* temp = dynamic_cast<T*>(displayable))
            return temp->GetHeight();
    }
    return 0;
}

template<typename T>
inline float InterfaceManager::GetClassWidth()
{
    for (auto displayable : displayables)
    {
	    if (T* temp = dynamic_cast<T*>(displayable))
            return temp->GetWidth();
    }
    return 0;
}
