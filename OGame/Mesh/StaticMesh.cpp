#include "StaticMesh.h"



StaticMesh::StaticMesh()
{
}


StaticMesh::~StaticMesh()
{
}

void StaticMesh::render()
{

}
void StaticMesh::createBuffers() 
{

	void* data;
	//Vertex buffer ====================================================================================================
	VkDeviceSize vertBufferSize = sizeof(Vertex) * vertex_amount;

	VkBuffer vertStagingBuffer;
	VkDeviceMemory vertStagingBufferMemory;
	createBuffer(vertBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertStagingBuffer, vertStagingBufferMemory);

	vkMapMemory(*renderer->getDevice() , vertStagingBufferMemory, 0, vertBufferSize, 0, &data);
	memcpy(data, vertexArray, (size_t)vertBufferSize);
	vkUnmapMemory(*renderer->getDevice(), vertStagingBufferMemory);

	createBuffer(vertBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copyBuffer(vertStagingBuffer, vertexBuffer, vertBufferSize);

	vkDestroyBuffer(*renderer->getDevice(), vertStagingBuffer, nullptr);
	vkFreeMemory(*renderer->getDevice(), vertStagingBufferMemory, nullptr);

	//index buffer ====================================================================================================
	VkDeviceSize indexBufferSize = sizeof(uint16_t) * index_amount;

	VkBuffer indexStagingBuffer;
	VkDeviceMemory indexStagingBufferMemory;
	createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, indexStagingBuffer, indexStagingBufferMemory);

	vkMapMemory(*renderer->getDevice(), indexStagingBufferMemory, 0, indexBufferSize, 0, &data);
	memcpy(data, indexArray, (size_t)indexBufferSize);
	vkUnmapMemory(*renderer->getDevice(), indexStagingBufferMemory);

	createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(indexStagingBuffer, indexBuffer, indexBufferSize);

	vkDestroyBuffer(*renderer->getDevice(), indexStagingBuffer, nullptr);
	vkFreeMemory(*renderer->getDevice(), indexStagingBufferMemory, nullptr);

	
}

void StaticMesh::setVertices(std::vector<glm::vec3>& _vertices)
{
	vertexArray = new Vertex[_vertices.size()];

	size_t vert_size = sizeof(_vertices[0]) * _vertices.size();
	std::memcpy(vertexArray, _vertices.data(), vert_size);
}
void StaticMesh::setindicies(std::vector<int>& _indicies)
{
	indexArray = new uint16_t[_indicies.size()];

	std::memcpy(indexArray, _indicies.data(), sizeof(int));
}
