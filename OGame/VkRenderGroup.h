#pragma once

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <vector>

#include "VulkanRenderer.h"



class VkRenderGroup
{
public:
	VkRenderGroup();
	~VkRenderGroup();

	void createCommandBuffers();

	void createDescriptorSet();

private:
	std::vector<VkCommandBuffer> commandBuffers;
	VkDescriptorSet descriptorSet;
	VkDescriptorSetLayout descriptorSetLayout;

	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;


	VulkanRenderer* renderer;

	//std::vector<PhysicalObject*> objects;
};

