#pragma once
#include "SpatialObject.h"
#include "Box2D.h"


class PhysicalObject :
	public SpatialObject
{
public:
	PhysicalObject();
	virtual ~PhysicalObject();

	class VkRenderTask* getTask();
	void createRenderTask(class VulkanRenderer* _renderer);
	void destroyRenderTask();

	class b2Body* getCollider();
	void createCollider(b2BodyDef* _body_def, b2FixtureDef* _fix_def, b2World*  _world);

	void update() {}

	void Tick();

protected:

	
	class VkRenderTask* task = nullptr;
	class b2Body* collider = nullptr;
};

