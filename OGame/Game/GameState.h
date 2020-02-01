#pragma once

#ifndef GameState_H
#define GameState_H

#include <chrono>

class GameState
{
public:
	GameState();
	~GameState();

	void Tick();

	double getTotalTime();
	double getDeltaTime();
	

private:
	
	std::chrono::time_point<std::chrono::steady_clock> start_time;
	std::chrono::time_point<std::chrono::steady_clock> current_time;

	double delta_time;

};

#endif
