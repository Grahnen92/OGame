#include "Level.h"
#include "GameInstance.h"
#include "Ogame/Entity/ActorComponent.h"
#include "Ogame/Entity/Actor.h"
#include "Box2D.h"

#include <iostream>

Level::Level() : physics_environment(nullptr), game_instance(nullptr)
{
}

Level::Level( GameInstance* _game_instance) : physics_environment(nullptr), game_instance(nullptr)
{
	game_instance = _game_instance;
}

Level::~Level()
{
	for (int i = 0; i < dynamic_components.size(); i++)
		delete dynamic_components[i];

	for (int i = 0; i < static_components.size(); i++)
		delete static_components[i];
}

void Level::markComponentForRegistration(OG::ActorComponent* _component)
{
	components_to_initialize.push_back(_component);
}

void Level::markComponentAsDynamic(OG::ActorComponent* _component) {
	dynamic_components.push_back(_component);
}
void Level::markComponentAsStatic(OG::ActorComponent* _component)
{
	static_components.push_back(_component);
}
//TODO: complete component and actor destruction. fix component structure. maybe remove component references from level?
void Level::markComponentForDestruction(OG::ActorComponent* _component)
{
	components_to_destroy.push_back(_component);
}

void Level::initLevel() {
	initComponents();
}

void Level::initComponents() {
	for (auto & component : components_to_initialize)
	{
		component->registerComponent();

		if (component->should_update)
			dynamic_components.push_back(component);
		else
			static_components.push_back(component);
	}

	components_to_initialize.clear();

	game_instance->sg_needs_update = true;
}

void Level::destroyComponents()
{

}


void Level::beginPlay() {

}
std::vector<OG::Actor*>* Level::getActors()
{
	return &actors;
}

std::vector<OG::ActorComponent*>* Level::getDynamicComponents()
{
	return &dynamic_components;
}
std::vector<OG::ActorComponent*>* Level::getStaticComponents()
{
	return &static_components;
}

void Level::createPhysicsEnvironment(glm::vec2 _gravity)
{
	physics_environment = new b2World(b2Vec2(_gravity.x, _gravity.y));
}

void Level::addActor(OG::Actor* _actor, const glm::mat4 & _transform)
{
	_actor->setTransform(_transform);
	actors.push_back(_actor);
	game_instance->sg_needs_update = true;
}
