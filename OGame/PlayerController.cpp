#include "PlayerController.h"
#include <iostream>
#include <algorithm>
#include "Pawn.h"


PlayerController::PlayerController()
{
	
}

PlayerController::PlayerController(GLFWwindow* _window)
{
	window = _window;
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetWindowUserPointer(window, this);
}


PlayerController::~PlayerController()
{

}

void PlayerController::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!glfwGetWindowUserPointer(window))
		throw std::runtime_error("callbacks on window with no attached playercontroller");
	
	PlayerController* this_controller = static_cast<PlayerController*>(glfwGetWindowUserPointer(window));
	if (this_controller->controlled_pawns.size() < 1)
		return;

	for (const auto & pawn : this_controller->controlled_pawns)
	{
		pawn->input_component->callKeyboardEvents(key, action);
	}

}

void  PlayerController::Possess( Pawn* _pawn)
{
	controlled_pawns.push_back(_pawn);
	_pawn->becomeHost(this);
}

bool  PlayerController::removePawn( Pawn* _pawn) {
	if (controlled_pawns.erase(std::remove(controlled_pawns.begin(), controlled_pawns.end(), _pawn)) != controlled_pawns.end())
		return true;
	else
		return false;
}

