#include "ShadowMapping.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace GigRenderer;

ShadowMapping::ShadowMapping()
{
}

ShadowMapping::~ShadowMapping()
{
}

void ShadowMapping::Init()
{
	GigRenderer::RENDERER.InitShadowMapping();

	auto* mainVertex = ResourceManager::Get<VertexShader>("Engine/Shaders/shadow.vert");
	auto* mainFragment = ResourceManager::Get<FragmentShader>("Engine/Shaders/shadow.frag");

	if (!shader.Link(mainVertex, mainFragment))
		std::cout << "Error linking drawLine shader" << std::endl;

	lightSpaceLocation = RENDERER.GetUniformLocation(shader.GetId(), "lightSpaceMatrix");
	modelLocation = RENDERER.GetUniformLocation(shader.GetId(), "model");
}

void ShadowMapping::BeginRender()
{
	shader.Use();
	GigRenderer::RENDERER.RenderShadowMapping();
}

void ShadowMapping::EndRender()
{
	shader.UnUse();
}

void ShadowMapping::Clear()
{
	GigRenderer::RENDERER.DeleteTexture(depthMap);
	GigRenderer::RENDERER.DeleteFrameBuffer(depthMapFBO);
}

void ShadowMapping::SendLight(lm::FMat4& mat)
{
	RENDERER.SetUniformValue(lightSpaceLocation, UniformType::MAT4, &mat);
}

void ShadowMapping::SendModel(lm::FMat4& mat)
{
	RENDERER.SetUniformValue(modelLocation, UniformType::MAT4, &mat);
}

unsigned int& ShadowMapping::GetdepthMapFBO()
{
	return depthMapFBO;
}

unsigned int& ShadowMapping::GetdepthMap()
{
	return depthMap;
}