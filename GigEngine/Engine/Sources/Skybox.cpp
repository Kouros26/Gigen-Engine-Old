#include "Renderer.h"
#include "Skybox.h"
#include "GameObjectManager.h"
#include <ResourceManager.h>
#include "Application.h"

using namespace GigRenderer;

Skybox::Skybox() : GameObject("SkyBox")
{
	SetModel(g_SkyboxModelPath);
	SetTexture(g_SkyboxTexturePath);
	GetTransform().AddRotation(lm::FVec3(180, 0, 0));

	VertexShader* mainVertex = ResourceManager::Get<VertexShader>("Engine/Shaders/vertSkybox.vert");
	FragmentShader* mainFragment = ResourceManager::Get<FragmentShader>("Engine/Shaders/fragSkybox.frag");

	if (!shaderProgram.Link(mainVertex, mainFragment))
		std::cout << "Error linking main shader" << std::endl;

	ModelLocation = RENDERER.GetUniformLocation(shaderProgram.GetId(), "model");
	viewProjLocation = RENDERER.GetUniformLocation(shaderProgram.GetId(), "viewProj");
	ColorLocation = RENDERER.GetUniformLocation(shaderProgram.GetId(), "textColor");
}

Skybox::~Skybox()
{
}

void Skybox::Draw()
{
	if (!IsActive()) return;

	shaderProgram.Use();

	if (Application::IsInEditor() || Application::IsUsingEditorCam())
	{
		GetTransform().SetWorldPosition(Application::GetEditorCamera().GetTransform().GetWorldPosition());
	}
	else if (Camera* cam = GameObjectManager::GetCurrentCamera())
	{
		GetTransform().SetWorldPosition(cam->GetTransform().GetWorldPosition());
	}

	RENDERER.SetUniformValue(viewProjLocation, UniformType::MAT4, &Application::GetViewProj());
	RENDERER.SetUniformValue(ModelLocation, UniformType::MAT4, &GetTransform().MatrixGetter());
	RENDERER.SetUniformValue(ColorLocation, UniformType::VEC3, &color);

	UpdateRender();

	shaderProgram.UnUse();
}

lm::FVec3& Skybox::GetColor()
{
	return color;
}

void Skybox::SetColor(lm::FVec3 col)
{
	color = col;
}