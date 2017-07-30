#include "SILevelOne.h"
#include "MaterialObject.h"
#include "PlaneMesh.h"
#include "SpaceshipFighter.h"
#include "VulkanRenderer.h"
#include "GameInstance.h"
#include "Player.h"


SILevelOne::SILevelOne()
{

}

SILevelOne::SILevelOne(GameInstance* _game_instance) : Level(_game_instance)
{
	PlaneMesh* plane_mesh = new PlaneMesh(glm::vec2(1.f, 1.f), _game_instance->getRenderer());
	addStaticMesh(plane_mesh); //0

	createPhysicsEnvironment(glm::vec2(0.f, 0.f));

	SpaceshipFighter* space_fighter = new SpaceshipFighter;
	space_fighter->getBodyDef()->type = b2_dynamicBody;
	space_fighter->getBodyDef()->position.Set(0.0f, 0.f);
	space_fighter->getBodyDef()->allowSleep = false;
	//bodyDef.gravityScale = 0.f;
	space_fighter->getBodyDef()->linearDamping = 0.f;
	b2PolygonShape space_fighterBox;
	space_fighterBox.SetAsBox(1.0f, 1.0);
	space_fighter->getFixtureyDef()->shape = &space_fighterBox;
	space_fighter->getFixtureyDef()->density = 10.0f;
	space_fighter->getFixtureyDef()->friction = 0.3f;
	space_fighter->getFixtureyDef()->restitution = 0.2f;
	addEntity(space_fighter);
	space_fighter->setStaticMesh(plane_mesh);

	//addSpatialEntity<SpatialObject>();

	Player* player_one = _game_instance->getPlayer(0);
	player_one->getController()->Possess(space_fighter);

	MaterialObject* ground = new MaterialObject;
	ground->getBodyDef()->type = b2_staticBody;
	ground->getBodyDef()->position.Set(0.0f, -10.0f);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(10.0f, 5.0f);
	ground->getFixtureyDef()->shape = &groundBox;
	ground->getFixtureyDef()->density =0.f;
	ground->getFixtureyDef()->friction = 0.3f;
	ground->getFixtureyDef()->restitution = 0.2f;
	addEntity(ground);
	ground->setStaticMesh(plane_mesh);
	ground->setScale(glm::vec3(10.f, 5.f, 1.f));

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;	
}
SILevelOne::~SILevelOne()
{

}
