#pragma once
#include <vector>
#include <string>

class VulkanRenderer;
class GameState;
class Level;
class Player;
class StaticMesh;

class GameInstance
{

	friend class Level;
public:
	GameInstance();
	virtual ~GameInstance() = 0;

	VulkanRenderer* getRenderer();

	GameState* getGameState();

	Level* getLevel();

	Player* getPlayer(int _player_index);

	StaticMesh* getStaticMesh(int _adress);

protected:

	virtual void createGame() = 0;
	virtual void createLevels() = 0;

	void createVulkanRenderer();
	void createGameState();
	void createPlayer();

	void loadStaticMesh(std::string _file);
	void addStaticMesh(StaticMesh* _mesh);

	void initGame();
	void mainLoop();

	void updateSceneGraph();

	VulkanRenderer* renderer = nullptr;

	std::vector<Player*> players;

	GameState* game_state = nullptr;

	Level* level = nullptr;

	std::vector<StaticMesh*> static_meshes;
	

private:

	bool sg_needs_update = false;

	void runGame();
	void cleanup();

};

