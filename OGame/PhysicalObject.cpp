#include "PhysicalObject.h"
#include "StaticMesh.h"
#include "VkRenderTask.h"
#include "VulkanRenderer.h"




PhysicalObject::PhysicalObject()
{
}


PhysicalObject::~PhysicalObject()
{
	if (task)
		delete task;
}



void PhysicalObject::createRenderTask(class VulkanRenderer* _renderer)
{
	task = new VkRenderTask(_renderer);
}

void PhysicalObject::destroyRenderTask()
{
	if (task)
		delete task;

	task = nullptr;
}

class VkRenderTask* PhysicalObject::getTask()
{
	return task;
}

class b2Body* PhysicalObject::getCollider()
{
	return collider;
}
void PhysicalObject::createCollider( b2BodyDef* _body_def, b2FixtureDef* _fix_def,  b2World*  _world)
{
	_body_def->position.Set(transform[3][0], transform[3][1]);
	collider = _world->CreateBody(_body_def);
	collider->CreateFixture(_fix_def);
}

void PhysicalObject::Tick() {
	if(collider)
		setPosition(&glm::vec3(collider->GetPosition().x, collider->GetPosition().y, transform[3][2]));

	task->updateUniformBuffer(transform);
}
