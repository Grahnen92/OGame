#include "Entity.h"
#include "Ogame/Game/Level.h"
#include "Ogame/Game/GameInstance.h"

OG::Entity::Entity()
{
}


OG::Entity::~Entity()
{
}


Level* OG::Entity::getLevel()
{
	return game_instance->getLevel();
}

GameInstance* OG::Entity::getGameInstance()
{
	return game_instance;
}