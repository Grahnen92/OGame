#include "VisualObject.h"
#include "VkRenderTask.h"
#include "StaticMesh.h"


VisualObject::VisualObject()
{

}

VisualObject::~VisualObject()
{
	if (task)
		delete task;
}

void VisualObject::createRenderTask(class VulkanRenderer* _renderer)
{
	task = new VkRenderTask(_renderer);
}

void VisualObject::destroyRenderTask()
{
	if (task)
		delete task;

	task = nullptr;
}

class VkRenderTask* VisualObject::getTask()
{
	return task;
}

void VisualObject::setStaticMesh(StaticMesh* _mesh)
{
	task->setMesh(_mesh);
}

void VisualObject::setPosition(const glm::vec3& _pos)
{
	SpatialObject::setPosition(_pos);
	task->updateUniformBuffer(transform);
}

void VisualObject::update() 
{
	task->updateUniformBuffer(transform); 
}