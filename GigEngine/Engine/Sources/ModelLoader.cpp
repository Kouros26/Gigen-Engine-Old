#include "ModelLoader.h"
#include "Mesh.h"
#include "Material.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include <assimp/scene.h>
#include <Vec3/FVec3.hpp>

void ModelLoader::LoadModel(std::vector<Mesh*>& meshes, std::vector<Material*>& materials, std::string const& pFilePath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(pFilePath, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "error loading assimp scene" << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene, meshes, materials);
}

void ModelLoader::ProcessNode(const aiNode* pNode, const aiScene* pScene, std::vector<Mesh*>& meshes, std::vector<Material*>& materials)
{
    for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
    {
        const aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
        ProcessMesh(mesh, pScene, meshes);
    }

    ProcessMaterial(pScene, materials);

    for (unsigned int i = 0; i < pNode->mNumChildren; i++)
        ProcessNode(pNode->mChildren[i], pScene, meshes, materials);
}

void ModelLoader::ProcessMesh(const aiMesh* pMesh, const aiScene* pScene, std::vector<Mesh*>& meshes)
{
    Mesh* mesh = new Mesh(pMesh->mNumVertices * VERTEX_SIZE, pMesh->mNumFaces * FACE_SIZE);
    mesh->vertices = new float[pMesh->mNumVertices * VERTEX_SIZE];
    mesh->materialIndex = pMesh->mMaterialIndex;

    for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
    {
        mesh->vertices[i * VERTEX_SIZE] = pMesh->mVertices[i].x;
        mesh->vertices[(i * VERTEX_SIZE) + 1] = pMesh->mVertices[i].y;
        mesh->vertices[(i * VERTEX_SIZE) + 2] = pMesh->mVertices[i].z;

        if (pMesh->HasNormals())
        {
            mesh->vertices[(i * VERTEX_SIZE) + 3] = pMesh->mNormals[i].x;
            mesh->vertices[(i * VERTEX_SIZE) + 4] = pMesh->mNormals[i].y;
            mesh->vertices[(i * VERTEX_SIZE) + 5] = pMesh->mNormals[i].z;
        }

        if (pMesh->mTextureCoords[0])
        {
            mesh->vertices[(i * VERTEX_SIZE) + 6] = pMesh->mTextureCoords[0][i].x;
            mesh->vertices[(i * VERTEX_SIZE) + 7] = pMesh->mTextureCoords[0][i].y;
        }
    }

    mesh->indices = new unsigned int[pMesh->mNumFaces * FACE_SIZE];

    for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
    {
        mesh->indices[(i * FACE_SIZE)] = pMesh->mFaces[i].mIndices[0];
        mesh->indices[(i * FACE_SIZE) + 1] = pMesh->mFaces[i].mIndices[1];
        mesh->indices[(i * FACE_SIZE) + 2] = pMesh->mFaces[i].mIndices[2];
    }

    meshes.emplace_back(mesh);
}

void ModelLoader::ProcessMaterial(const aiScene* pScene, std::vector<Material*>& materials)
{
    for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
    {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        Material* m = new Material();

        //diffuse & ambient are inverted ??
        aiColor4D vec4;
        if (AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &vec4))
        {
            m->SetAmbient(lm::FVec3(vec4.r, vec4.g, vec4.b));
        }
        if (AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_AMBIENT, &vec4))
        {
            m->SetDiffuse(lm::FVec3(vec4.r, vec4.g, vec4.b));
        }
        if (AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_SPECULAR, &vec4))
        {
            m->SetSpecular(lm::FVec3(vec4.r, vec4.g, vec4.b));
        }

        unsigned int max;
        float shininess;
        aiGetMaterialFloatArray(pMaterial, AI_MATKEY_SHININESS, &shininess, &max);

        m->SetShininess(shininess);

        materials.push_back(m);
    }
}