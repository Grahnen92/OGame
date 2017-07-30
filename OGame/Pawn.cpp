#include "Pawn.h"
#include "PlayerController.h"


Pawn::Pawn()
{
}


Pawn::~Pawn()
{
	if (input_component)
		delete input_component;
}


void Pawn::becomeHost( PlayerController* _player)
{
	owning_player = _player;

	createPlayerInputComponent();
	SetupPlayerInputComponent();
}
