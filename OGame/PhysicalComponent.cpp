#include "PhysicalComponent.h"
#include "Actor.h"
#include "Level.h"
#include <iostream>

OG::PhysicalComponent::PhysicalComponent()
{
	
}

OG::PhysicalComponent::PhysicalComponent( Actor* _owner) : SpatialComponent(_owner)
{
}


OG::PhysicalComponent::~PhysicalComponent()
{
}

void OG::PhysicalComponent::registerComponent()
{
	SpatialComponent::registerComponent();
	createCollider(&body_def, &fixture_def, owner->getLevel()->getPhysicsEnvironment());
	if (body_def.type == b2_dynamicBody)
	{
		should_update = true;
	}
	else {
		should_update = false;
	}
}

b2Body* OG::PhysicalComponent::getCollider()
{
	return collider;
}

void OG::PhysicalComponent::createCollider(b2BodyDef* _body_def, b2FixtureDef* _fix_def, b2World*  _world)
{
	if (_world)
	{
		//TODO: fix
		//_body_def->angle 
		_body_def->position.Set(transform[3][0], transform[3][1]);
		collider = _world->CreateBody(_body_def);
		for (int i = 0; i < body_shape.m_count; i++) {
			body_shape.m_vertices[i].x = body_shape.m_vertices[i].x*transform[0][0];
			body_shape.m_vertices[i].y = body_shape.m_vertices[i].y*transform[1][1];
		}
		_fix_def->shape = &body_shape;
		collider->CreateFixture(_fix_def);
	}
	else {
		std::cout << "trying to create body for physicalcomponent when there is no physics simulation running";
	}
}

void OG::PhysicalComponent::setPosition(const glm::vec3& _Position)
{
	SpatialComponent::setPosition(_Position);
	if (collider)
		collider->SetTransform(b2Vec2(_Position.x, _Position.y), collider->GetAngle());
}
void OG::PhysicalComponent::setRotation(const glm::mat3& _rotation)
{
	SpatialComponent::setRotation(_rotation);
	//TODO: Fix
	if (collider)
		collider->SetTransform(collider->GetPosition(), 0.f);
}
void OG::PhysicalComponent::setTransform(const glm::mat4& _transform)
{
	SpatialComponent::setTransform(_transform);
	//TODO: Fix
	if(collider)
		collider->SetTransform(b2Vec2(_transform[3][0], _transform[3][1]), 0.f);
}

void OG::PhysicalComponent::update() 
{
	SpatialComponent::update();

	if (collider)
		SpatialComponent::setPosition(&glm::vec3(collider->GetPosition().x, collider->GetPosition().y, transform[3][2]));
}
