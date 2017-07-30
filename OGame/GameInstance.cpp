#include "GameInstance.h"
#include "VulkanRenderer.h"
#include "Player.h"
#include "GameState.h"
#include "VkRenderTask.h"
#include "Level.h"
#include "MaterialObject.h"


GameInstance::GameInstance()
{
}




GameInstance::~GameInstance()
{
	if (level)
		delete level;
	if (renderer)
		delete renderer;
	if (game_state)
		delete game_state;
}

void GameInstance::initGame()
{

	createGameState();

	std::vector<VkRenderTask*> render_tasks;

	
	for (auto & object : *level->getStaticEntities())
	{
		render_tasks.push_back(object->getTask());
		object->update();
	}
		

	for (auto & object : *level->getDynamicEntities())
	{
		render_tasks.push_back(object->getTask());
		object->update();
	}
		

	renderer->recordCommandBuffer(render_tasks);
}

void GameInstance::mainLoop()
{
	while (!glfwWindowShouldClose(renderer->getWindow())) {
		glfwPollEvents();
		game_state->Tick();
		if (level->getPhysicsEnvironment())
		{
			level->getPhysicsEnvironment()->Step(game_state->getDeltaTime(), 6, 4);
		}
		

		for (const auto & object : *level->getDynamicEntities())
		{
			object->update();
		}

		//space_fighter.tick();

		renderer->updateCamera(game_state);
		renderer->updateUniformBuffer();
		renderer->drawFrame();
	}
}

VulkanRenderer*  GameInstance::getRenderer()
{
	return renderer;
}

GameState*  GameInstance::getGameState()
{
	return game_state;
}

Level* GameInstance::getLevel()
{
	return level;
}

Player* GameInstance::getPlayer(int _player_index)
{
	if (_player_index > players.size() - 1)
	{
		return nullptr;
	}
	else
	{
		return players[_player_index];
	}
}

void GameInstance::createVulkanRenderer()
{
	renderer = new VulkanRenderer;
	try {
		renderer->init();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		delete renderer;
		renderer = nullptr;
		return;
	}
}

void GameInstance::createGameState()
{
	game_state = new GameState;
}


void GameInstance::createPlayer()
{
	if (renderer)
		players.push_back(new Player(renderer->getWindow()));
	else {
		throw std::runtime_error("cannot create players before the game is initialized.");
	}
}