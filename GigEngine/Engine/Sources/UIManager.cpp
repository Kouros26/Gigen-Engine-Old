#include "UIManager.h"
#include "UIImage.h"
#include "UIText.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Mat4/FMat4.hpp"
#include "Vec3/FVec3.hpp"
#include "Application.h"
#include "GameObjectManager.h"

using namespace GigRenderer;

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
	for (const UIElement* elem : elements)
		delete elem;

	for (const UIElement* elem : worldElements)
		delete elem;
}

void UIManager::Init()
{
	auto* mainVertex = ResourceManager::Get<VertexShader>("Engine/Shaders/UIVertText.vert");
	auto* mainFragment = ResourceManager::Get<FragmentShader>("Engine/Shaders/UIFragText.frag");

	if (!shaderProgram.Link(mainVertex, mainFragment))
		std::cout << "Error linking UI shader" << std::endl;

	ISWORLDLocation = GigRenderer::RENDERER.GetUniformLocation(shaderProgram.GetId(), "isWorld");
	PROJECTIONLocation = GigRenderer::RENDERER.GetUniformLocation(shaderProgram.GetId(), "projection");
	ORTHOLocation = GigRenderer::RENDERER.GetUniformLocation(shaderProgram.GetId(), "ortho");
	MODELLocation = GigRenderer::RENDERER.GetUniformLocation(shaderProgram.GetId(), "model");
	COLORLocation = GigRenderer::RENDERER.GetUniformLocation(shaderProgram.GetId(), "textColor");
	IMAGELocation = GigRenderer::RENDERER.GetUniformLocation(shaderProgram.GetId(), "isImage");
}

void UIManager::AddImageElement()
{
	AddToUIElements(new UIImage());
}

void UIManager::AddTextElement()
{
	AddToUIElements(new UIText());
}

void UIManager::DrawUI()
{
	shaderProgram.Use();
	RENDERER.Enable(RD_DEPTH_TEST);

	RENDERER.SetUniformValue(ORTHOLocation, GigRenderer::UniformType::MAT4, &Application::GetWindow().GetOrthoMatrix());
	RENDERER.SetUniformValue(PROJECTIONLocation, GigRenderer::UniformType::MAT4, &Application::GetViewProj());

	int isWorld = 1;

	RENDERER.SetUniformValue(ISWORLDLocation, GigRenderer::UniformType::INT, &isWorld);

	for (UIElement* elem : worldElements)
	{
		if (elem->IsActive())
		{
			RENDERER.SetUniformValue(MODELLocation, GigRenderer::UniformType::MAT4, &elem->GetTransform().MatrixGetter());
			RENDERER.SetUniformValue(IMAGELocation, GigRenderer::UniformType::INT, &elem->GetIsImage());
			RENDERER.SetUniformValue(COLORLocation, GigRenderer::UniformType::VEC3, &elem->GetColor());
			elem->Draw();
		}
	}

	RENDERER.Disable(RD_DEPTH_TEST);
	isWorld = 0;
	RENDERER.SetUniformValue(ISWORLDLocation, GigRenderer::UniformType::INT, &isWorld);

	for (UIElement* elem : elements)
	{
		if (elem->IsActive())
		{
			RENDERER.SetUniformValue(IMAGELocation, GigRenderer::UniformType::INT, &elem->GetIsImage());
			RENDERER.SetUniformValue(COLORLocation, GigRenderer::UniformType::VEC3, &elem->GetColor());
			elem->Draw();
		}
	}

	shaderProgram.UnUse();
}

int UIManager::GetUISize()
{
	return elements.size();
}

int UIManager::GetWorldSize()
{
	return worldElements.size();
}

std::vector<UIElement*>& UIManager::GetUIElements()
{
	return elements;
}

std::vector<UIElement*>& UIManager::GetWorldElements()
{
	return worldElements;
}

UIElement* UIManager::GetUIElement(unsigned int i)
{
	if (i < GetUISize())
	{
		return elements.at(i);
	}
	return nullptr;
}

UIElement* UIManager::GetWorldElement(unsigned int i)
{
	if (i < GetWorldSize())
	{
		return worldElements.at(i);
	}
	return nullptr;
}

void UIManager::SetFocusedElement(UIElement* elem)
{
	focusedElement = elem;
	if (elem)
		GameObjectManager::SetFocusedGameObject(nullptr);
}

UIElement* UIManager::GetFocusedElement()
{
	return focusedElement;
}

void UIManager::RemoveElement(UIElement* elem)
{
	auto it = std::ranges::find(elements, elem);

	if (it != elements.end())
	{
		elements.erase(it);
		elem->~UIElement();
		return;
	}

	it = std::ranges::find(worldElements, elem);

	if (it != worldElements.end())
	{
		worldElements.erase(it);
		elem->~UIElement();
		return;
	}
}

UIElement* UIManager::CreateUIElement(UIElement* elem)
{
	const auto newElem = new UIElement(*elem);

	return AddToUIElements(newElem);
}

UIElement* UIManager::AddToWorldElements(UIElement* elem)
{
	const auto it = std::ranges::find(worldElements, elem);

	if (it == worldElements.end())
	{
		const auto it2 = std::ranges::find(elements, elem);
		if (it2 != elements.end())
			elements.erase(it2);

		worldElements.push_back(elem);
	}

	return elem;
}

UIElement* UIManager::AddToUIElements(UIElement* elem)
{
	const auto it = std::ranges::find(elements, elem);

	if (it == elements.end())
	{
		const auto it2 = std::ranges::find(worldElements, elem);
		if (it2 != worldElements.end())
			worldElements.erase(it2);

		elements.push_back(elem);
	}

	return elem;
}