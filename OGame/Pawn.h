#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "InputComponent.h"
#include "MaterialObject.h"
#include "VisualObject.h"
#include <GLFW/glfw3.h>



class Pawn : public MaterialObject
{

	friend class PlayerController;

public:
	Pawn();

	virtual ~Pawn();

	

	class PlayerController* getOwningPlayer() { return owning_player; }

protected:

	void becomeHost(class PlayerController* _player);

	void createPlayerInputComponent() { input_component = new InputComponent; }
	virtual void SetupPlayerInputComponent() = 0;
	void destroyPlayerInputComponent() { delete input_component; }

	class PlayerController* owning_player = nullptr;
	class InputComponent* input_component = nullptr;
};

#endif