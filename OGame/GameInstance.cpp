#include "GameInstance.h"

#include "VulkanRenderer.h"
#include "VkRenderTask.h"
#include "StaticMesh.h"

#include "Player.h"

#include "Level.h"
#include "GameState.h"

#include "Actor.h"
#include "MeshComponent.h"



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

	for (int i = 0; i < static_meshes.size(); i++)
		delete static_meshes[i];
}

void GameInstance::initGame()
{

	createGameState();

	

	if (level)
	{
		updateSceneGraph();
	}
	else
	{
		throw std::runtime_error("trying to start game with no created level");
	}
}

void GameInstance::updateSceneGraph()
{
	std::vector<VkRenderTask*> render_tasks;
	for (auto & object : *level->getDynamicComponents())
	{
		object->update();
		render_tasks.push_back(dynamic_cast<OG::MeshComponent*>(object)->getTask());
	}

	for (auto & object : *level->getStaticComponents())
	{
		object->update();
		render_tasks.push_back(dynamic_cast<OG::MeshComponent*>(object)->getTask());
	}

	renderer->recordCommandBuffer(render_tasks);
	sg_needs_update = false;
}

void GameInstance::mainLoop()
{
	while (!glfwWindowShouldClose(renderer->getWindow())) {
		glfwPollEvents();
		game_state->Tick();
		
		if (level->getPhysicsEnvironment())
			level->getPhysicsEnvironment()->Step(game_state->getDeltaTime(), 6, 4);
		if (level->components_to_initialize.size() > 0)
			level->initComponents();
		if (sg_needs_update)
			updateSceneGraph();
		
		for (const auto & component : *level->getDynamicComponents())
			component->update();

		for (const auto & actor : *level->getActors())
			actor->update(game_state->getDeltaTime());

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

void GameInstance::loadStaticMesh(std::string _file)
{

}
void GameInstance::addStaticMesh(StaticMesh* _mesh)
{
	static_meshes.push_back(_mesh);
}

StaticMesh* GameInstance::getStaticMesh(int _adress)
{
	if (_adress < static_meshes.size())
		return static_meshes[_adress];
	else
		std::cout << "trying to acess mesh that doesn't exist";
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