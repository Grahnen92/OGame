#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	if (vertexArray)
		delete[] vertexArray;

	if (indexArray)
		delete[] indexArray;

	if(renderer)
		destroyBuffers();
}

void Mesh::setRenderer(VulkanRenderer* _renderer)
{
	renderer = _renderer;
}

void Mesh::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(*(renderer->getDevice()), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(*(renderer->getDevice()), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = renderer->findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(*(renderer->getDevice()), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(*(renderer->getDevice()), buffer, bufferMemory, 0);
}


void Mesh::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = *renderer->getCommandPool();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(*(renderer->getDevice()), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(*renderer->getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(*renderer->getGraphicsQueue());

	vkFreeCommandBuffers(*(renderer->getDevice()), *renderer->getCommandPool(), 1, &commandBuffer);
}

void Mesh::destroyBuffers()
{
	vkDestroyBuffer(*renderer->getDevice(), indexBuffer, nullptr);
	vkFreeMemory(*renderer->getDevice(), indexBufferMemory, nullptr);

	vkDestroyBuffer(*renderer->getDevice(), vertexBuffer, nullptr);
	vkFreeMemory(*renderer->getDevice(), vertexBufferMemory, nullptr);
}

