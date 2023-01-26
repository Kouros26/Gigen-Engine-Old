#pragma once
#include "Vertex.h"
#include <vector>

struct VerticesAndIndices {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};

class Mesh
{
public:
	Mesh();
	Mesh(VerticesAndIndices* verticesAndIndices);
	~Mesh();

	VerticesAndIndices* verticesAndIndices;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	bool isInit = false;
};