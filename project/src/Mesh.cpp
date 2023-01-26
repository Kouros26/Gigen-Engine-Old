#include "Mesh.h"
#include "Application.h"

Mesh::Mesh()
{
}

Mesh::Mesh(VerticesAndIndices* verticesAndIndices)
	:verticesAndIndices(verticesAndIndices)
{
}

Mesh::~Mesh()
{
	if (!isInit)
		return;

	VkDevice device = *Application::GetDevice();

	vkDestroyBuffer(device, indexBuffer, nullptr);
	vkFreeMemory(device, indexBufferMemory, nullptr);

	vkDestroyBuffer(device, vertexBuffer, nullptr);
	vkFreeMemory(device, vertexBufferMemory, nullptr);

	vkDestroyDescriptorPool(device, descriptorPool, nullptr);

	for (size_t j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
		vkDestroyBuffer(device, uniformBuffers[j], nullptr);
		vkFreeMemory(device, uniformBuffersMemory[j], nullptr);
	}
}