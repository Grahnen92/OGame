#include "SILevelOne.h"
//#include "Pawn.h"
#include "SpaceshipFighter.h"
#include "Ogame/Mesh/StaticMeshActor.h"
#include "Ogame/Mesh/MeshComponent.h"

#include "Ogame/Rendering/VulkanRenderer.h"

#include "Ogame/Game/Player.h"
//#include "Level.h"
#include "Ogame/Game/GameInstance.h"

SILevelOne::SILevelOne()
{

}

SILevelOne::SILevelOne(GameInstance* _game_instance) : Level(_game_instance)
{

	
}
SILevelOne::~SILevelOne()
{

}


void SILevelOne::setupLevel()
{
	createPhysicsEnvironment(glm::vec2(0.f,-10.f));

	glm::mat4 sf_transform(1.0);
	sf_transform = glm::translate(sf_transform, glm::vec3(0.f, 1.f, 0.f));
	SpaceshipFighter* sf = spawnActor<SpaceshipFighter>(sf_transform);
	sf->mesh->setStaticMesh(0);

	Player* player_one = game_instance->getPlayer(0);
	player_one->getController()->Possess(sf);

	glm::mat4 ground_transform;
	ground_transform = glm::mat4(1.0);
	ground_transform = glm::translate(sf_transform, glm::vec3(0.f, -6.f, 0.f));
	ground_transform = glm::scale(ground_transform, glm::vec3(10.f, 1, 1.f));
	StaticMeshActor* ground = spawnActor<StaticMeshActor>(ground_transform);

	glm::mat4 rw_transform(1.0);
	rw_transform = glm::translate(rw_transform, glm::vec3(11.f, 0.f, 0.f));
	rw_transform = glm::scale(rw_transform, glm::vec3(1.f, 5.f, 1.f));
	StaticMeshActor* right_wall = spawnActor<StaticMeshActor>(rw_transform);

	glm::mat4 lw_transform(1.0);
	lw_transform = glm::translate(lw_transform, glm::vec3(-11.f, 0.f, 0.f));
	lw_transform = glm::scale(lw_transform, glm::vec3(1.f, 5.f, 1.f));
	StaticMeshActor* left_wall = spawnActor<StaticMeshActor>(lw_transform);

	glm::mat4 sphere_transform(1.0);
	lw_transform = glm::translate(sphere_transform, glm::vec3(-11.f, 2.f, 0.f));
	lw_transform = glm::scale(sphere_transform, glm::vec3(10.f, 10.f, 10.f));
	StaticMeshActor* sphere = spawnActor<StaticMeshActor>(sphere_transform);
	sphere->mesh->setStaticMesh(1);

	//// Prepare for simulation. Typically we use a time step of 1/60 of a
	//// second (60Hz) and 10 iterations. This provides a high quality simulation
	//// in most game scenarios.
	//float32 timeStep = 1.0f / 60.0f;
	//int32 velocityIterations = 6;
	//int32 positionIterations = 2;	
}