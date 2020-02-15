#include "Ogame/OGame/OGameInstance.h"
#include "Ogame/OGame/SILevelOne.h"
#include "Ogame/Mesh/PlaneMesh.h"
#include "Ogame/Mesh/SphereMesh.h"


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
	PlaneMesh* planeMesh = new PlaneMesh(glm::vec2(1.f, 1.f), getRenderer());
	addStaticMesh(planeMesh); //0
	SphereMesh* sphereMesh = new SphereMesh(0.5f, getRenderer());
	addStaticMesh(sphereMesh); //1

	level = new SILevelOne(this);
	level->setupLevel();
	level->initLevel();

}