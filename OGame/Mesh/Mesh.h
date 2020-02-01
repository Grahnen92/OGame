#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <vector>

#include "Ogame/Rendering/VulkanRenderer.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};

		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}

};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void setRenderer(VulkanRenderer* _renderer);
	VulkanRenderer* getRenderer() { return renderer; }

	VkBuffer* getVertexBuffer() { return &vertexBuffer; }
	VkBuffer* getIndexBuffer() { return &indexBuffer; }

protected:

	virtual void render() = 0;
	virtual void createBuffers() = 0;
	void destroyBuffers();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	Vertex* vertexArray = nullptr;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	uint16_t* indexArray = nullptr;

	VulkanRenderer* renderer;
	
};

