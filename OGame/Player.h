#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerController.h"
class Player
{
public:
	
	Player(GLFWwindow* _window);
	~Player();

	PlayerController* getController() { return controller; }

private:
	Player();

	PlayerController* controller = nullptr;
};

#endif