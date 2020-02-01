#include "VkRenderTask.h"



VkRenderTask::VkRenderTask()
{
	

}

VkRenderTask::VkRenderTask(VulkanRenderer* _renderer)
{
	renderer = _renderer;
	createUniformBuffer();
	createDescriptorSet();
	
}

VkRenderTask::~VkRenderTask()
{
	if(renderer)
		cleanup();
}

VkDescriptorSet* VkRenderTask::getDescriptorSet()
{
	return &descriptorSet;
}

void VkRenderTask::createDescriptorSet()
{
	VkDescriptorSetLayout layouts[] = { *renderer->getmDescriptorSetLayout() };
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = *renderer->getDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = layouts;

	if (vkAllocateDescriptorSets(*renderer->getDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor set!");
	}

	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(mUniformBufferObject);

	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &bufferInfo;
	descriptorWrite.pImageInfo = nullptr; // Optional
	descriptorWrite.pTexelBufferView = nullptr; // Optional

	vkUpdateDescriptorSets(*renderer->getDevice(), 1, &descriptorWrite, 0, nullptr);
}
void VkRenderTask::createUniformBuffer() {
	VkDeviceSize bufferSize = sizeof(mUniformBufferObject);
	renderer->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);
}

void VkRenderTask::updateUniformBuffer(const glm::mat4& _model_transform) {
	mUniformBufferObject ubo = {};

	ubo.model = _model_transform;

	void* data;
	vkMapMemory(*renderer->getDevice(), uniformBufferMemory, 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(*renderer->getDevice(), uniformBufferMemory);
}

StaticMesh* VkRenderTask::getMesh()
{
	return mesh;
}

void VkRenderTask::setMesh(class StaticMesh* _mesh)
{
	mesh = _mesh;
}

void VkRenderTask::cleanup()
{
	vkDestroyBuffer(*renderer->getDevice(), uniformBuffer, nullptr);
	vkFreeMemory(*renderer->getDevice(), uniformBufferMemory, nullptr);
	renderer = nullptr;
}
