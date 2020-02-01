#include "Actor.h"
#include "Ogame/Game/GameInstance.h"
#include "Ogame/Game/Level.h"
#include "Ogame/Game/GameInstance.h"
#include "Ogame/Entity/SpatialComponent.h"

#include <algorithm>

OG::Actor::Actor()
{
}

OG::Actor::Actor(GameInstance* _gi)
{
	game_instance = _gi;
}


OG::Actor::~Actor()
{
}

OG::ActorComponent* OG::Actor::findComponent(OG::ActorComponent* _component)
{
	for (const auto & component : components)
		if (component == _component)
			return component;

	return nullptr;
}

bool OG::Actor::removeComponent(OG::ActorComponent* _component)
{
	if (components.erase(std::remove(components.begin(), components.end(), _component)) != components.end())
		return true;
	else
		return false;
}

void OG::Actor::update(float delta_time)
{

}

bool OG::Actor::setTransform(const glm::mat4& _transform)
{
	if (root_component)
	{
		root_component->setTransform(_transform);
		return true;
	}
	else
	{
		return false;
	}
}
		
bool OG::Actor::setPosition(const glm::vec3& _position)
{
	return false;
}
bool OG::Actor::setRotation(const glm::vec3& _rotation)
{
	return false;
}
bool OG::Actor::setScale(const glm::vec3& _scale)

{
	return false;
}