#include "Model.h"

#include "DrawLine.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Vec3/FVec3.hpp"

Model::Model(std::string const& pFilePath)
    :IResource(pFilePath)
{
    LoadModel(meshes, materials,boneMap,boneCounter, pFilePath);
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

    for (const auto mesh : meshes)
    {
        if (mesh)
        {
            if (mesh->materialIndex < materials.size())
            {
                if (materials[mesh->materialIndex])
                {
                    materials[mesh->materialIndex]->SendToShader();
                }
                else
                {
                    Material::SendDefaultMaterial();
                }
            }
            mesh->Draw();

            if (!boneMap.empty())
                DrawSkeleton();
        }
    }
    Texture::UnBind();
}

void Model::DrawSkeleton() const
{
    //lm::FVec3 start{ boneMap.find("root")->second.offset.m_matrix->x, boneMap.find("root")->second.offset.m_matrix->y, boneMap.find("root")->second.offset.m_matrix->z };
    //lm::FVec3 end{ boneMap.find("pelvis")->second.offset.m_matrix->x, boneMap.find("pelvis")->second.offset.m_matrix->y, boneMap.find("pelvis")->second.offset.m_matrix->z };
    //Lines::DrawLine(start, end, { 0,1,0 }, 0);
}

void Model::Init()
{
    for (const auto& mesh : meshes)
        mesh->SetupBuffers();
}

std::map<std::string, BoneInfo>& Model::GetBoneInfoMap()
{
    return boneMap;
}

int& Model::GetBoneCount()
{
    return boneCounter;
}