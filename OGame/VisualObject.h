#pragma once
#include "SpatialObject.h"
class VisualObject :
	public virtual SpatialObject
{
public:
	VisualObject();
	virtual ~VisualObject();

	class VkRenderTask* getTask();
	void createRenderTask(class VulkanRenderer* _renderer);
	void destroyRenderTask();

	void setStaticMesh(class StaticMesh* _mesh);

	
	void setPosition(const glm::vec3 & _Position) override;

	void update();



protected:

	class VkRenderTask* task = nullptr;
};

