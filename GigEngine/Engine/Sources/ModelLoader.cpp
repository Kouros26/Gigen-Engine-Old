#include "ModelLoader.h"
#include "Mesh.h"
#include "Material.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include <assimp/scene.h>
#include <Vec3/FVec3.hpp>
#include "Model.h"
#include <cassert>
#include "Quaternion/FQuat.hpp"
#include "Animation.h"
#include <assimp/anim.h>

void ModelLoader::LoadModel(std::vector<Mesh*>& meshes, std::vector<Material*>& materials, std::map<std::string, BoneInfo>& boneInfo, int& boneCounter, std::string const& pFilePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pFilePath, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals/* | aiProcess_FlipUVs*/);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "error loading assimp scene" << std::endl;
		return;
	}

	ProcessNode(scene->mRootNode, scene, meshes, materials, boneInfo, boneCounter);
}

void ModelLoader::ProcessNode(const aiNode* pNode, const aiScene* pScene, std::vector<Mesh*>& meshes, std::vector<Material*>& materials, std::map<std::string, BoneInfo>& boneInfo, int& boneCounter)
{
	for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
	{
		const aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
		ProcessMesh(mesh, pScene, meshes, boneInfo, boneCounter);
	}

	ProcessMaterial(pScene, materials);

	for (unsigned int i = 0; i < pNode->mNumChildren; i++)
		ProcessNode(pNode->mChildren[i], pScene, meshes, materials, boneInfo, boneCounter);
}

void ModelLoader::ProcessMesh(const aiMesh* pMesh, const aiScene* pScene, std::vector<Mesh*>& meshes, std::map<std::string, BoneInfo>& boneInfo, int& boneCounter)
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

		for (int j = 0; j < MAX_BONE_INFLUENCE; ++j)
		{
			mesh->vertices[(i * VERTEX_SIZE) + 8 + j] = -1.0f;
			mesh->vertices[(i * VERTEX_SIZE) + 12 + j] = 0;
		}
	}

	mesh->indices = new unsigned int[pMesh->mNumFaces * FACE_SIZE];

	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		mesh->indices[(i * FACE_SIZE)] = pMesh->mFaces[i].mIndices[0];
		mesh->indices[(i * FACE_SIZE) + 1] = pMesh->mFaces[i].mIndices[1];
		mesh->indices[(i * FACE_SIZE) + 2] = pMesh->mFaces[i].mIndices[2];
	}

	ProcessBones(pMesh, pScene, mesh, boneInfo, boneCounter);

	meshes.emplace_back(mesh);
}

void ModelLoader::ProcessBones(const aiMesh* pMesh, const aiScene* pScene, Mesh* mesh, std::map<std::string, BoneInfo>& boneInfo, int& boneCounter)
{
	for (int boneIndex = 0; boneIndex < pMesh->mNumBones; ++boneIndex)
	{
		int boneId = -1;
		std::string boneName = pMesh->mBones[boneIndex]->mName.C_Str();

		if (!boneInfo.contains(boneName))
		{
			BoneInfo newBoneInfo;
			newBoneInfo.id = boneCounter;
			newBoneInfo.offset = AIMat4toFMat4(pMesh->mBones[boneIndex]->mOffsetMatrix);
			boneInfo[boneName] = newBoneInfo;
			boneId = boneCounter;
			boneCounter++;
		}

		else
			boneId = boneInfo[boneName].id;

		const auto weights = pMesh->mBones[boneIndex]->mWeights;
		const int numWeights = pMesh->mBones[boneIndex]->mNumWeights;

		for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
		{
			const int vertexId = weights[weightIndex].mVertexId;
			const float weight = weights[weightIndex].mWeight;
			SetVertexBoneData(mesh, vertexId, boneId, weight);
		}
	}
}

void ModelLoader::ProcessMaterial(const aiScene* pScene, std::vector<Material*>& materials)
{
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		auto m = new Material();

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

void ModelLoader::SetVertexBoneData(const Mesh* pMesh, int pVertexId, int pId, float pWeight)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
	{
		if (pMesh->vertices[(pVertexId * VERTEX_SIZE) + 8 + i] < 0)
		{
			pMesh->vertices[(pVertexId * VERTEX_SIZE) + 8 + i] = pId;
			pMesh->vertices[(pVertexId * VERTEX_SIZE) + 12 + i] = pWeight;
			break;
		}
	}
}

lm::FMat4 ModelLoader::AIMat4toFMat4(const aiMatrix4x4& pMatrix)
{
	return { pMatrix.a1, pMatrix.b1, pMatrix.c1, pMatrix.d1,
			pMatrix.a2, pMatrix.b2, pMatrix.c2, pMatrix.d2,
			pMatrix.a3, pMatrix.b3, pMatrix.c3, pMatrix.d3,
			pMatrix.a4, pMatrix.b4, pMatrix.c4, pMatrix.d4 };
}

lm::FVec3 ModelLoader::AIVec3ToFVec3(const aiVector3D& pVector)
{
	return { pVector.x, pVector.y, pVector.z };
}

lm::FQuat ModelLoader::AIQuatToFQuat(const aiQuaternion& pQuaternion)
{
	return { pQuaternion.x, pQuaternion.y, pQuaternion.z, pQuaternion.w };
}

void ModelLoader::LoadAnimation(std::string& pAnimationPath, class Model*& pModel, double& pDuration, double& pTicksPerSecond, std::map<std::string, BoneInfo>& pBoneMap, NodeData& RootNode, std::vector<class Bone>& pBones)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pAnimationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	const auto animation = scene->mAnimations[0];
	pDuration = animation->mDuration;
	pTicksPerSecond = animation->mTicksPerSecond;
	ReadHierarchyData(RootNode, scene->mRootNode->mChildren[0]);
	ReadMissingBones(animation, *pModel, pBones, pBoneMap);
}

void ModelLoader::ReadMissingBones(const aiAnimation* pAnimation, Model& pModel, std::vector<class Bone>& pBones, std::map<std::string, BoneInfo>& pBoneMap)
{
	const unsigned int size = pAnimation->mNumChannels;

	auto& boneInfoMap = pModel.GetBoneInfoMap();
	int& boneCount = pModel.GetBoneCount();

	//reading channels(bones engaged in an animation and their keyframes)
	for (unsigned int i = 0; i < size; i++)
	{
		const auto channel = pAnimation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (!boneInfoMap.contains(boneName))
		{
			boneInfoMap[boneName].id = boneCount;
			boneCount++;
		}
		pBones.emplace_back(channel->mNodeName.data,
			boneInfoMap[channel->mNodeName.data].id, channel);
	}

	pBoneMap = boneInfoMap;
}

void ModelLoader::ReadHierarchyData(NodeData& pOutData, const aiNode* pNode)
{
	assert(pNode);

	pOutData.name = pNode->mName.data;
	pOutData.transform = ModelLoader::AIMat4toFMat4(pNode->mTransformation);
	pOutData.childrenCount = pNode->mNumChildren;

	for (unsigned int i = 0; i < pNode->mNumChildren; i++)
	{
		NodeData newData;
		ReadHierarchyData(newData, pNode->mChildren[i]);
		pOutData.children.push_back(newData);
	}
}