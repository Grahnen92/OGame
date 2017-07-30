#include "PresentObject.h"



PresentObject::PresentObject()
{
}


PresentObject::~PresentObject()
{
}

b2Body* PresentObject::getCollider()
{
	return collider;
}

void PresentObject::createCollider(b2BodyDef* _body_def, b2FixtureDef* _fix_def, b2World*  _world)
{
	//_body_def->position.Set(transform[3][0], transform[3][1]);
	collider = _world->CreateBody(_body_def);
	collider->CreateFixture(_fix_def);
}

void PresentObject::setPosition(const glm::vec3& _pos)
{
	SpatialObject::setPosition(_pos);
	body_def.position.Set(_pos.x, _pos.y);
	collider->SetTransform(b2Vec2(_pos.x, _pos.y), collider->GetAngle());
}

void PresentObject::update() {
	if (collider)
		SpatialObject::setPosition(&glm::vec3(collider->GetPosition().x, collider->GetPosition().y, transform[3][2]));

}