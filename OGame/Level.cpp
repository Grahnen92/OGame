#include "Level.h"
#include "MaterialObject.h"
#include "GameInstance.h"


Level::Level() : physics_environment(nullptr), game_instance(nullptr)
{
}

Level::Level( GameInstance* _game_instance) : physics_environment(nullptr), game_instance(nullptr)
{
	game_instance = _game_instance;
}

Level::~Level()
{
	for (int i = 0; i < immaterial_entities.size(); i++)
		delete immaterial_entities[i];

	for (int i = 0; i < dynamic_entities.size(); i++)
		delete dynamic_entities[i];

	for (int i = 0; i < static_entities.size(); i++)
		delete static_entities[i];

	for (int i = 0; i < static_meshes.size(); i++)
		delete static_meshes[i];

}

std::vector<Entity*>* Level::getImmaterialEntities()
{
	return &immaterial_entities;
}
std::vector<MaterialObject*>* Level::getDynamicEntities()
{
	return &dynamic_entities;
}
std::vector<VisualObject*>* Level::getStaticEntities()
{
	return &static_entities;
}

void Level::addEntity( Entity* _entity)
{
	MaterialObject* m_obj = dynamic_cast<MaterialObject*>(_entity);
	if (m_obj)
	{
		if (m_obj->getBodyDef()->type == b2_staticBody)
		{
			m_obj->createCollider(m_obj->getBodyDef(), m_obj->getFixtureyDef(), getPhysicsEnvironment());
			addStaticEntity(m_obj);
		}
		else
		{
			addDynamicEntity(m_obj);
		}
		return;
	}

	VisualObject* v_obj = dynamic_cast<VisualObject*>(_entity);
	if (v_obj)
	{
		addStaticEntity(v_obj);
		return;
	}

	immaterial_entities.push_back(_entity);
}

void Level::addStaticEntity( VisualObject* _entity)
{
	_entity->createRenderTask(game_instance->getRenderer());
	static_entities.push_back(_entity);

}
void Level::addDynamicEntity( MaterialObject* _entity)
{
	_entity->createCollider(_entity->getBodyDef(), _entity->getFixtureyDef(), getPhysicsEnvironment());
	_entity->createRenderTask(game_instance->getRenderer());
	dynamic_entities.push_back(_entity);
}

void Level::loadStaticMesh(std::string _file)
{

}
void Level::addStaticMesh(class StaticMesh* _mesh)
{
	static_meshes.push_back(_mesh);
}

void Level::createPhysicsEnvironment(glm::vec2 _gravity)
{
	physics_environment = new b2World(b2Vec2(_gravity));
}


