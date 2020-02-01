#include "StaticMeshActor.h"
#include "Ogame/Game/Level.h"
#include "MeshComponent.h"

StaticMeshActor::StaticMeshActor()
{
}

StaticMeshActor::StaticMeshActor(GameInstance* _gi) : Actor(_gi)
{
	mesh = createDefaultComponent<OG::MeshComponent>();
	root_component = mesh;

	mesh->setStaticMesh(0);
	mesh->getBodyDef()->type = b2_staticBody;
	mesh->getBodyDef()->position.Set(0.0f, 0.f);
	mesh->getBodyShape()->SetAsBox(1.f, 1.f);
	mesh->getFixtureyDef()->shape = mesh->getBodyShape();
	mesh->getFixtureyDef()->density = 0.f;
	mesh->getFixtureyDef()->friction = 0.f;
	mesh->getFixtureyDef()->restitution = 0.f;
	mesh->setScale(glm::vec3(1.f, 1.f, 1.f));
}


StaticMeshActor::~StaticMeshActor()
{
}

void StaticMeshActor::update(float delta_time) {

}