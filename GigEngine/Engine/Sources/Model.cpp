#include "Model.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"

Model::Model(std::string const& pFilePath)
    :IResource(pFilePath)
{
    LoadModel(meshes, materials, pFilePath);
}

Model::Model(const Model& other)
{
    for (const auto& mesh : other.meshes)
        meshes.push_back(new Mesh(*mesh));
}

Model::Model(Model&& other) noexcept
{
    for (const auto& mesh : other.meshes)
        meshes.push_back(mesh);
    other.meshes.clear();
}

Model::~Model()
{
    for (const auto& mesh : meshes)
    {
        delete mesh;
    }
    for (const auto& mat : materials)
    {
        delete mat;
    }
}

Model& Model::operator=(const Model& other)
{
    if (this == &other)
        return *this;

    for (const auto& mesh : other.meshes)
        meshes.push_back(new Mesh(*mesh));

    return *this;
}

Model& Model::operator=(Model&& other) noexcept
{
    if (this == &other)
        return *this;
    for (const auto& mesh : other.meshes)
        meshes.push_back(mesh);
    other.meshes.clear();

    return *this;
}

void Model::Draw(Texture* texture) const
{
    if (texture) 
    {
        texture->Bind();
    }

    for (int i = 0; i < meshes.size(); i++)
    {
        if (meshes[i])
        {
            if (meshes[i]->materialIndex < materials.size())
            {
                if (materials[meshes[i]->materialIndex])
                {
                    materials[meshes[i]->materialIndex]->SendToShader();
                }
                else
                {
                    Material::SendDefaultMaterial();
                }
            }
            meshes[i]->Draw();
        }
    }
    Texture::UnBind();
}

void Model::Init()
{
    for (const auto& mesh : meshes)
        mesh->SetupBuffers();
}