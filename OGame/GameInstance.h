#pragma once


#include <vector>

class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	class VulkanRenderer* getRenderer();

	class GameState* getGameState();

	class Level* getLevel();

	class Player* getPlayer(int _player_index);

protected:

	virtual void createGame() = 0;
	virtual void createLevels() = 0;

	void createVulkanRenderer();
	void createGameState();
	void createPlayer();

	void initGame();
	void mainLoop();

	class VulkanRenderer* renderer;

	std::vector<class Player*> players;

	class GameState* game_state;

	class Level* level;

	

private:

	void runGame();
	void cleanup();

};

