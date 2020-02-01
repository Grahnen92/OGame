#include "SpaceshipFighter.h"
#include <iostream>
#include "MeshComponent.h"
#include "InputComponent.h"
#include <GLFW/glfw3.h>
#include "Level.h"
#include "b2RaycastCallbackClosestHit.h"

#include "StaticMeshActor.h"

#include <math.h>

SpaceshipFighter::SpaceshipFighter()
{


}

SpaceshipFighter::SpaceshipFighter(GameInstance* _gi) : Pawn(_gi)
{
	mesh = createDefaultComponent<OG::MeshComponent>();
	root_component = mesh;

	mesh->setStaticMesh(0);
	mesh->getBodyDef()->type = b2_dynamicBody;
	mesh->getBodyDef()->position.Set(0.0f, 0.f);
	mesh->getBodyDef()->allowSleep = false;
	//bodyDef.gravityScale = 0.f;
	mesh->getBodyDef()->linearDamping = 0.f;
	mesh->getBodyShape()->SetAsBox(1.0f, 1.0);
	mesh->getFixtureyDef()->shape = mesh->getBodyShape();
	mesh->getFixtureyDef()->density = 10.0f;
	mesh->getFixtureyDef()->friction = 0.3f;
	mesh->getFixtureyDef()->restitution = 0.2f;

	setupPIDS();
}


SpaceshipFighter::~SpaceshipFighter()
{
}

void SpaceshipFighter::SetupPlayerInputComponent()
{
	input_component->addKeyBoardEvent(GLFW_KEY_E, GLFW_ANY_RELEASE_BEHAVIOR, &SpaceshipFighter::shoot, this);
	input_component->addKeyBoardEvent(GLFW_KEY_LEFT, GLFW_PRESS, &SpaceshipFighter::goLeft, this);
	input_component->addKeyBoardEvent(GLFW_KEY_LEFT, GLFW_RELEASE, &SpaceshipFighter::stopGoingLeft, this);
	input_component->addKeyBoardEvent(GLFW_KEY_RIGHT, GLFW_PRESS, &SpaceshipFighter::goRight, this);
	input_component->addKeyBoardEvent(GLFW_KEY_RIGHT, GLFW_RELEASE, &SpaceshipFighter::stopGoingRight, this);

}

void SpaceshipFighter::update(float delta_time) 
{
	controlMovement(delta_time);
	hover(delta_time);
	
}

void SpaceshipFighter::hover(float delta_time)
{
	b2RayCastCallbackClosestHit hover_ray;

	hover_ray.setFixtureToIgnore(mesh->getCollider()->GetFixtureList());
	getLevel()->getPhysicsEnvironment()->RayCast(&hover_ray, mesh->getCollider()->GetPosition(), mesh->getCollider()->GetPosition() + b2Vec2(0.f, -10.f));
	if (hover_ray.didHit())
	{
		HitInfo* hit = hover_ray.getClosestHit();
		b2Vec2 hit_distance = mesh->getCollider()->GetPosition() - hit->point;
	
		hover_pid.error = hover_pid.target - hit_distance.Length();
		hover_pid.integral = hover_pid.integral + hover_pid.error * delta_time;
		hover_pid.derivative = (hover_pid.error - hover_pid.prev_err) / delta_time;

		hover_pid.adjustment =
			hover_pid.P * hover_pid.error +
			hover_pid.I * hover_pid.integral +
			hover_pid.D * hover_pid.derivative;
		hover_pid.adjustment = std::min(std::max(0.0f, hover_pid.adjustment), hover_pid.max_adjustment) * mesh->getCollider()->GetMass();

		hover_pid.prev_err = hover_pid.error;
		
		b2Vec2 adj_force = b2Vec2(0.f, 1.f);
		adj_force *= hover_pid.adjustment;
		mesh->getCollider()->ApplyForceToCenter(adj_force, true);

	}
	else
	{
		hover_pid.prev_err = 0.0;
		hover_pid.integral = 0.0;
	}

	hover_ray.reset();
}

void SpaceshipFighter::shoot( )
{
	std::cout << "Shoot her!\n";

	//collider->ApplyForce(b2Vec2(0.f, 1.f), b2Vec2(0.f, 0.f), true);
	//collider->ApplyForceToCenter(b2Vec2(1000.f, 1000.f), true);

	glm::mat4 bullet_transform;
	bullet_transform = *root_component->getTransformM();
	bullet_transform = glm::translate(bullet_transform, glm::vec3(0.f, 1.f, 0.f));
	bullet_transform = glm::scale(bullet_transform, glm::vec3(0.1f, 0.1f, 0.1f));

	StaticMeshActor* bullet = getLevel()->spawnActor<StaticMeshActor>(bullet_transform);

	

	OG::MeshComponent*  bullet_mesh = bullet->findFirstComponentOfClass<OG::MeshComponent>();
	bullet_mesh->getBodyDef()->type = b2_dynamicBody;
	//bullet->setTransform()
}

void SpaceshipFighter::controlMovement(float delta_time) 
{
	glm::vec2 dunnoWhatToCallThisVec = movement_pid.target * movement_dir;
	b2Vec2 error_vec = b2Vec2(dunnoWhatToCallThisVec.x, dunnoWhatToCallThisVec.y) - mesh->getCollider()->GetLinearVelocity();
	movement_pid.error.x = error_vec.x; movement_pid.error.y = error_vec.y;

	movement_pid.integral = movement_pid.integral + movement_pid.error * delta_time;
	movement_pid.derivative = (movement_pid.error - movement_pid.prev_err) / delta_time;

	movement_pid.adjustment =
		movement_pid.P * movement_pid.error +
		movement_pid.I * movement_pid.integral +
		movement_pid.D * movement_pid.derivative;
	//movement_pid.adjustment.x = std::min(std::max(0.0f, movement_pid.adjustment.x), movement_pid.max_adjustment.x) * mesh->getCollider()->GetMass();
	//movement_pid.adjustment.y = std::min(std::max(0.0f, movement_pid.adjustment.y), movement_pid.max_adjustment.y) * mesh->getCollider()->GetMass();
	movement_pid.adjustment = movement_pid.adjustment * mesh->getCollider()->GetMass();

	movement_pid.prev_err = movement_pid.error;

	b2Vec2 adj_force = b2Vec2(movement_pid.adjustment.x, movement_pid.adjustment.y);
	mesh->getCollider()->ApplyForceToCenter(adj_force, true);
}

void SpaceshipFighter::goLeft()
{
	//mesh->getCollider()->ApplyForceToCenter(b2Vec2(-10000.f, 0.f), true);
	movement_dir = glm::vec2(-1.f, 0.f);
}
void SpaceshipFighter::stopGoingLeft()
{	
	if(movement_dir.x == -1.f)
		movement_dir = glm::vec2(0.f, 0.f);
}

void SpaceshipFighter::goRight()
{
	//mesh->getCollider()->ApplyForceToCenter(b2Vec2(10000.f, 0.f), true);
	movement_dir = glm::vec2(1.f, 0.f);
}
void SpaceshipFighter::stopGoingRight()
{
	if (movement_dir.x == 1.f)
		movement_dir = glm::vec2(0.f, 0.f);
}

void SpaceshipFighter::setupPIDS()
{
	hover_pid.P = 100.f;
	hover_pid.I = 0.f;
	hover_pid.D = 5.f;
	hover_pid.max_adjustment = 1000.f;
	hover_pid.target = 2.f;

	movement_pid.P = glm::vec2(10.f, 0.f);
	movement_pid.I = glm::vec2(0.f, 0.f);
	movement_pid.D = glm::vec2(0.f, 0.f);
	movement_pid.max_adjustment = glm::vec2(1000.f, 1000.f);
	movement_pid.target = glm::vec2(5.f, 5.f);

}