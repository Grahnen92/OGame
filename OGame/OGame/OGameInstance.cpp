#include "Ogame/OGame/OGameInstance.h"
#include "Ogame/OGame/SILevelOne.h"
#include "Ogame/Mesh/PlaneMesh.h"


OGameInstance::OGameInstance()
{
	createGame();
	createLevels();
	initGame();
	mainLoop();
}


OGameInstance::~OGameInstance()
{
}


void OGameInstance::createGame()
{
	createVulkanRenderer();
	createPlayer();

}

void OGameInstance::createLevels()
{
	PlaneMesh* plane_mesh = new PlaneMesh(glm::vec2(1.f, 1.f), getRenderer());
	addStaticMesh(plane_mesh); //0
	level = new SILevelOne(this);
	level->setupLevel();
	level->initLevel();

}