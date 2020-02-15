#pragma once

#include "StaticMesh.h"

class SphereMesh : public StaticMesh 
{
public:

	SphereMesh() = default;

	// Creates a sphere  
	SphereMesh(float _rad, class VulkanRenderer* _renderer);
	~SphereMesh();

	void createSphere(float radius, int segments);

};