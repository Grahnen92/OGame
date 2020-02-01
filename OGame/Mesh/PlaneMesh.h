#pragma once
#include "StaticMesh.h"
class PlaneMesh :
	public StaticMesh
{
public:
	PlaneMesh();
	PlaneMesh(glm::vec2 _dims);
	PlaneMesh(glm::vec2 _dims, class VulkanRenderer* _renderer);
	~PlaneMesh();
};

