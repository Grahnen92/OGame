#pragma once

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <vector>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class PlayerController
{
public:
	PlayerController();
	PlayerController(GLFWwindow* _window);
	~PlayerController();

	void Possess(class Pawn*);
	bool removePawn(class Pawn*);

	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	GLFWwindow* window;

	std::vector<class Pawn*> controlled_pawns;

};

#endif // ! 

