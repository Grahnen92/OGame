#include "VkRenderGroup.h"
#include "StaticMesh.h"


VkRenderGroup::VkRenderGroup()
{
}


VkRenderGroup::~VkRenderGroup()
{
}


void VkRenderGroup::createCommandBuffers()
{
	////command buffer ====================================================================================================
	//commandBuffers.resize(renderer->getSwapChainFrameBuffers()->size());

	//VkCommandBufferAllocateInfo allocInfo = {};
	//allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	//allocInfo.commandPool = *renderer->getCommandPool();
	//allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	//allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	//if (vkAllocateCommandBuffers(*renderer->getDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
	//	throw std::runtime_error("failed to allocate command buffers!");
	//}

	//for (size_t i = 0; i < commandBuffers.size(); i++) {
	//	VkCommandBufferBeginInfo beginInfo = {};
	//	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	//	beginInfo.pInheritanceInfo = nullptr; // Optional

	//	vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

	//	VkRenderPassBeginInfo renderPassInfo = {};
	//	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	//	renderPassInfo.renderPass = *renderer->getRenderPass();
	//	renderPassInfo.framebuffer = (*renderer->getSwapChainFrameBuffers())[i];
	//	renderPassInfo.renderArea.offset = { 0, 0 };
	//	renderPassInfo.renderArea.extent = *renderer->getSwapChainExtent();

	//	std::array<VkClearValue, 2> clearValues = {};
	//	clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
	//	clearValues[1].depthStencil = { 1.0f, 0 };
	//	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	//	renderPassInfo.pClearValues = clearValues.data();

	//	vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	//	vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *renderer->getGraphicsPipeline());

	//	for (const auto &object : objects)
	//	{
	//		
	//		VkBuffer vertexBuffers[] = { *object->getMesh()->getVertexBuffer() };
	//		VkDeviceSize offsets[] = { 0 };
	//		vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

	//		vkCmdBindIndexBuffer(commandBuffers[i], *object->getMesh()->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);

	//		vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *renderer->getPipeLineLayout(), 0, 1, renderer->getDescriptorSet(), 0, nullptr);

	//		//vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);
	//		vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

	//	}

	//	vkCmdEndRenderPass(commandBuffers[i]);

	//	if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to record command buffer!");
	//	}
	//}
}

void VkRenderGroup::createDescriptorSet()
{
	//VkDescriptorSetLayout layouts[] = { descriptorSetLayout };
	//VkDescriptorSetAllocateInfo allocInfo = {};
	//allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	//allocInfo.descriptorPool = *renderer->getDescriptorPool();
	//allocInfo.descriptorSetCount = 1;
	//allocInfo.pSetLayouts = layouts;

	//if (vkAllocateDescriptorSets(*renderer->getDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
	//	throw std::runtime_error("failed to allocate descriptor set!");
	//}

	//VkDescriptorBufferInfo bufferInfo = {};
	//bufferInfo.buffer = uniformBuffer;
	//bufferInfo.offset = 0;
	//bufferInfo.range = sizeof(objects.size()*sizeof(glm::mat4));

	//VkWriteDescriptorSet descriptorWrite = {};
	//descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	//descriptorWrite.dstSet = descriptorSet;
	//descriptorWrite.dstBinding = 0;
	//descriptorWrite.dstArrayElement = 0;
	//descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	//descriptorWrite.descriptorCount = 1;
	//descriptorWrite.pBufferInfo = &bufferInfo;
	//descriptorWrite.pImageInfo = nullptr; // Optional
	//descriptorWrite.pTexelBufferView = nullptr; // Optional

	//vkUpdateDescriptorSets(*renderer->getDevice(), 1, &descriptorWrite, 0, nullptr);
}