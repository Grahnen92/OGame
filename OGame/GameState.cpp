#include "GameState.h"




GameState::GameState()
{
	start_time = std::chrono::high_resolution_clock::now();
	current_time = std::chrono::high_resolution_clock::now();
	delta_time = 0.0;
}


GameState::~GameState()
{

}

void GameState::Tick()
{
	std::chrono::time_point<std::chrono::steady_clock> tmp_current_time = std::chrono::high_resolution_clock::now();

	delta_time = std::chrono::duration_cast<std::chrono::microseconds>(tmp_current_time  - current_time).count() / 1000000.0;
	current_time = tmp_current_time;
}

double GameState::getTotalTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() / 1000.0;
}

double GameState::getDeltaTime()
{
	return delta_time;
}
