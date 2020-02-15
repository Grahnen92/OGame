#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanRenderer.h"

class ModelRenderObject
{
public:
	ModelRenderObject();
	ModelRenderObject(VulkanRenderer* _renderer);
	~ModelRenderObject();
	
	void createDescriptorSet();
	VkDescriptorSet* getDescriptorSet();

	void createUniformBuffer();

	void updateUniformBuffer(const glm::mat4& _model_transform);

	class StaticMesh* getMesh();
	void setMesh(class StaticMesh* _mesh);

	void cleanup();

protected:
	VkDescriptorSet descriptorSet;

	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;

	VulkanRenderer* renderer;

	class StaticMesh* mesh = nullptr;
};

