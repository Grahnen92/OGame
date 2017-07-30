#include "MaterialObject.h"
#include "VkRenderTask.h"

MaterialObject::MaterialObject()
{
}


MaterialObject::~MaterialObject()
{

}

void MaterialObject::setPosition(const glm::vec3 & _pos)
{
	SpatialObject::setPosition(_pos);
	body_def.position.Set(_pos.x, _pos.y);
	collider->SetTransform(b2Vec2(_pos.x, _pos.y), collider->GetAngle());

	task->updateUniformBuffer(transform);
}

void MaterialObject::update()
{
	if (collider)
		SpatialObject::setPosition(&glm::vec3(collider->GetPosition().x, collider->GetPosition().y, transform[3][2]));

	task->updateUniformBuffer(transform);

}
