#pragma once
#include "Mesh.h"
#include <vector>
class StaticMesh :
	public Mesh
{
public:
	StaticMesh();
	~StaticMesh();

	void render() override;
	void createBuffers() override;

	void loadFromFile() {}
	void setVertices(std::vector<glm::vec3>& _vertices);
	void setindicies(std::vector<int>& _indicies);

	int getVertexAmount() { return vertex_amount; }
	int getIndexAmount() { return index_amount; }

protected:
	int vertex_amount;
	int index_amount;

	//std::vector<Vertex> vertices;
	//std::vector<uint16_t> indicies;
};

