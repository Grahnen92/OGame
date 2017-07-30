#include "SpaceshipFighter.h"
#include <iostream>


SpaceshipFighter::SpaceshipFighter()
{
}


SpaceshipFighter::~SpaceshipFighter()
{
}


void SpaceshipFighter::SetupPlayerInputComponent()
{
	input_component->addKeyBoardEvent(GLFW_KEY_E, GLFW_ANY_RELEASE_BEHAVIOR, &SpaceshipFighter::shoot, this);
	input_component->addKeyBoardEvent(GLFW_KEY_LEFT, GLFW_REPEAT, &SpaceshipFighter::goLeft, this);
	input_component->addKeyBoardEvent(GLFW_KEY_RIGHT, GLFW_REPEAT, &SpaceshipFighter::goRight, this);

}

void SpaceshipFighter::shoot( )
{
	std::cout << "Shoot her!\n";

	//collider->ApplyForce(b2Vec2(0.f, 1.f), b2Vec2(0.f, 0.f), true);
	//collider->ApplyForceToCenter(b2Vec2(1000.f, 1000.f), true);

	
}

void SpaceshipFighter::goLeft()
{
	collider->ApplyForceToCenter(b2Vec2(-10000.f, 0.f), true);
}

void SpaceshipFighter::goRight()
{
	collider->ApplyForceToCenter(b2Vec2(10000.f, 0.f), true);
}