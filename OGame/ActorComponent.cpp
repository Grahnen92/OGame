#include "ActorComponent.h"
#include "Actor.h"
#include "Level.h"


OG::ActorComponent::ActorComponent()
{
}

OG::ActorComponent::ActorComponent(Actor* _owner)
{
	owner = _owner;

	_owner->getLevel()->markComponentForRegistration(this);
}

OG::ActorComponent::~ActorComponent()
{
}

void OG::ActorComponent::registerComponent()
{
}

void OG::ActorComponent::destroy()
{
	owner->removeComponent(this);
	owner->getLevel();
}

void OG::ActorComponent::update()
{

}
