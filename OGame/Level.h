#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "Pawn.h"

class GameInstance;
class StaticMesh;
class b2World;

namespace OG {
	class ActorComponent;
	class Actor;
	class Pawn;
}


class Level
{

	friend class GameInstance;

public:
	
	Level(GameInstance* _game_instance);

	virtual ~Level();

	std::vector<OG::Actor*>* getActors();
	std::vector<OG::ActorComponent*>* getDynamicComponents();
	std::vector<OG::ActorComponent*>* getStaticComponents();

	b2World* getPhysicsEnvironment() { return physics_environment; }

	void markComponentForRegistration(OG::ActorComponent* _component);
	void markComponentAsDynamic(OG::ActorComponent* _component);
	void markComponentAsStatic(OG::ActorComponent* _component);
	void initComponents();

	void markComponentForDestruction(OG::ActorComponent* _component);
	void destroyComponents();

	virtual void setupLevel() = 0;
	void initLevel();
	

	void beginPlay();

	template<class C>
	C* spawnActor(const glm::mat4& _transform) {
		C* actor = new C(game_instance);
		//actor->SetTransform(_transform);
		//actors.push_back(actor);
		addActor(actor, _transform);

		return actor;
	}

protected:
	Level();
	
	void createPhysicsEnvironment(glm::vec2 _gravity);

	GameInstance* game_instance;
	b2World* physics_environment;

private:

	std::vector<OG::ActorComponent*> components_to_initialize;
	std::vector<OG::ActorComponent*> components_to_destroy;

	std::vector<OG::Actor*> actors;
	std::vector<OG::Pawn*> pawns;

	std::vector<OG::ActorComponent*> dynamic_components;
	std::vector<OG::ActorComponent*> static_components;

	void addActor(OG::Actor* _actor, const glm::mat4 & _transform);

	
};

#endif // !LEVEL_H