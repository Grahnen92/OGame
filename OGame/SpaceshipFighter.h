#pragma once
#include "Pawn.h"
class SpaceshipFighter :
	public Pawn
{
public:
	SpaceshipFighter();
	~SpaceshipFighter();

private:
	void SetupPlayerInputComponent() override;

	void shoot();

	void goLeft();
	void goRight();
};

