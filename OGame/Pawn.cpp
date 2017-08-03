#include "Pawn.h"
#include "PlayerController.h"
#include "InputComponent.h"

OG::Pawn::Pawn()
{
}
OG::Pawn::Pawn(GameInstance* _gi) : Actor(_gi)
{

}


OG::Pawn::~Pawn()
{
	if (input_component)
		delete input_component;
}

void OG::Pawn::createPlayerInputComponent()
{ 
	input_component = new InputComponent; 
}


void OG::Pawn::becomeHost( PlayerController* _player)
{
	owning_player = _player;

	createPlayerInputComponent();
	SetupPlayerInputComponent();
}

void OG::Pawn::update(float delta_time)
{

}
