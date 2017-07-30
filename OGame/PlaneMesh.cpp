#include "PlaneMesh.h"



PlaneMesh::PlaneMesh()
{
}

PlaneMesh::PlaneMesh(glm::vec2 _dims)
{
	const std::vector<Vertex> tmp_vertices = {
		{ { -0.5f*_dims.x, -0.5f*_dims.y, 0.f },	{ 0.0f, 0.0f, 1.0f },	{ 1.0f, 0.0f, 0.0f } },
		{ { 0.5f*_dims.x, -0.5f*_dims.y, 0.f },		{ 0.0f, 0.0f, 1.0f },	{ 0.0f, 1.0f, 0.0f } },
		{ { 0.5f*_dims.x, 0.5f*_dims.y, 0.f },		{ 0.0f, 0.0f, 1.0f },	{ 0.0f, 0.0f, 1.0f } },
		{ { -0.5f*_dims.x, 0.5f*_dims.y, 0.f },		{ 0.0f, 0.0f, 1.0f },	{ 1.0f, 1.0f, 1.0f } },
	};

	vertexArray = new Vertex[tmp_vertices.size()];
	
	//memcpy(vertexArray, tmp_vertices.data(), (size_t)sizeof(Vertex)*tmp_vertices.size);

	for (int i = 0; i < tmp_vertices.size(); i++)
		vertexArray[i] = tmp_vertices[i];

	const std::vector<uint16_t> tmp_indices = {
		0, 1, 2, 2, 3, 0,
	};

	indexArray = new uint16_t[tmp_indices.size()];

	//memcpy(indexArray, tmp_indices.data(), (size_t)sizeof(int)*tmp_indices.size);
	for (int i = 0; i < tmp_indices.size(); i++)
		indexArray[i] = tmp_indices[i];

}

PlaneMesh::PlaneMesh(glm::vec2 _dims, class VulkanRenderer* _renderer)
{
	renderer = _renderer;

	const std::vector<Vertex> tmp_vertices = {
		{ { -1.f*_dims.x, -1.f*_dims.y, 0.f },{ 0.0f, 0.0f, 1.0f },{ 0.8f, 0.5f, 0.0f } },
		{ { 1.f*_dims.x, -1.f*_dims.y, 0.f },{ 0.0f, 0.0f, 1.0f },{ 0.8f, 0.5f, 0.0f } },
		{ { 1.f*_dims.x, 1.f*_dims.y, 0.f },{ 0.0f, 0.0f, 1.0f },{ 0.8f, 0.5f, 0.0f } },
		{ { -1.f*_dims.x, 1.f*_dims.y, 0.f },{ 0.0f, 0.0f, 1.0f },{ 0.8f, 0.5f, 0.0f } },
	};
	//TODO: removedebug
	//vertices = tmp_vertices;
	//=============

	vertex_amount = tmp_vertices.size();

	vertexArray = new Vertex[vertex_amount];
	
	//memcpy(vertexArray, tmp_vertices.data(), (size_t)sizeof(Vertex)*tmp_vertices.size);

	for (int i = 0; i < vertex_amount; i++)
		vertexArray[i] = tmp_vertices[i];

	const std::vector<uint16_t> tmp_indices = {
		0, 1, 2, 2, 3, 0,
	};
	//TODO: removedebug
	//indicies = tmp_indices;
	//=============

	index_amount = tmp_indices.size();

	indexArray = new uint16_t[index_amount];

	//memcpy(indexArray, tmp_indices.data(), (size_t)sizeof(int)*tmp_indices.size);
	for (int i = 0; i < index_amount; i++)
		indexArray[i] = tmp_indices[i];

	createBuffers();
}

PlaneMesh::~PlaneMesh()
{
}

