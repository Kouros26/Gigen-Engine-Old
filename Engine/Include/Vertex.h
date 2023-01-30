#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Mat4/Mat4.h"
#include "Mat3/Mat3.h"
#include "Vec2/Vec2.h"
#include "Vec3/Vec3.h"
#include <array>

class Vertex {
public:
	Vertex(lm::vec3 pos, lm::vec3 color, lm::vec2 texCoord);
	lm::vec3 pos;
	lm::vec3 color;
	lm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

struct UniformBufferModel {
	lm::mat4 model;
};

struct UniformBufferGlobal {
	lm::mat4 viewProj;
	lm::vec3 viewPos;
};