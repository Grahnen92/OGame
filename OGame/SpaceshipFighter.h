#pragma once

#ifndef SPACESHIPFIGHTER_H
#define SPACESHIPFIGHTER_H

#include "Pawn.h"

class b2RayCastCallbackClosestHit;

namespace OG {
	class MeshComponent;
}

struct PIDData
{

	float target;

	float error = 0.f;
	float prev_err = 0.f;
	float integral = 0.f;
	float derivative = 0.f;
	float adjustment = 0.f;

	float max_adjustment;
	float P;
	float I;
	float D;
};


struct PIDData2D
{

	glm::vec2 target = glm::vec2(0.f, 0.f);

	glm::vec2 error = glm::vec2(0.f, 0.f);
	glm::vec2 prev_err = glm::vec2(0.f, 0.f);
	glm::vec2 integral = glm::vec2(0.f, 0.f);
	glm::vec2 derivative = glm::vec2(0.f, 0.f);
	glm::vec2 adjustment = glm::vec2(0.f, 0.f);

	glm::vec2 max_adjustment = glm::vec2(0.f, 0.f);

	glm::vec2 P = glm::vec2(0.f, 0.f);
	glm::vec2 I = glm::vec2(0.f, 0.f);
	glm::vec2 D = glm::vec2(0.f, 0.f);
};

class SpaceshipFighter :
	public OG::Pawn
{
public:
	SpaceshipFighter();
	SpaceshipFighter( GameInstance* _gi);
	~SpaceshipFighter();

	OG::MeshComponent* mesh;

	void update(float delta_time) final;

private:
	void SetupPlayerInputComponent() override;

	void setupPIDS();

	void shoot();

	PIDData2D movement_pid;
	glm::vec2 movement_dir;
	void controlMovement(float delta_time);

	void goLeft();
	void stopGoingLeft();
	void goRight();
	void stopGoingRight();


	PIDData hover_pid;
	void hover(float delta_time);
	//b2RayCastCallbackClosestHit hover_ray;

	
};

#endif // !SPACESHIPFIGHTER_H