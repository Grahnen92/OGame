#pragma once

#include <vector>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Level
{
public:
	 
	~Level();

	std::vector<class Entity*>* getImmaterialEntities();
	std::vector<class MaterialObject*>* getDynamicEntities();
	std::vector<class VisualObject*>* getStaticEntities();

	class b2World* getPhysicsEnvironment() { return physics_environment; }


protected:
	Level();
	Level(class GameInstance* _game_instance);

	template<class C>
	void addEntity() {

	}

	template<class C>
	void addSpatialEntity() {
		dynamic_entities.push_back(new C);
	}

	void addEntity(class Entity* _entity);
	void removeEntity(class Entity* _entity);


	void addStaticEntity(class VisualObject* _entity);
	void addDynamicEntity(class MaterialObject* _entity);

	void loadStaticMesh(std::string _file);
	void addStaticMesh(class StaticMesh* _mesh);

	
	void createPhysicsEnvironment(glm::vec2 _gravity);

private:

	std::vector<class Pawn*> pawns;

	std::vector<class Entity*> immaterial_entities;
	std::vector<class MaterialObject*> dynamic_entities;
	std::vector<class VisualObject*> static_entities;

	std::vector<class StaticMesh*> static_meshes;

	class GameInstance* game_instance;

	class b2World* physics_environment;
};

