#include "OGameInstance.h"
#include "SILevelOne.h"


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
	level = new SILevelOne(this);

}