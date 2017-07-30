#include "Player.h"



Player::Player()
{
}

Player::Player(GLFWwindow* _window)
{
	controller = new PlayerController(_window);
}

Player::~Player()
{
	if (controller)
		delete controller;
}
