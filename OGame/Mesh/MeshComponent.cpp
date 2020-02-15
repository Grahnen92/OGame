#include "MeshComponent.h"
#include "Ogame/Rendering/ModelRenderObject.h"
#include "StaticMesh.h"
#include "Ogame/Entity/Actor.h"
#include "Ogame/Game/GameInstance.h"


OG::MeshComponent::MeshComponent() 
	: mesh_adress(-1)
	, m_model(nullptr)
{
}

OG::MeshComponent::MeshComponent(Actor* _owner) : PhysicalComponent(_owner)
{
	MeshComponent();
}

OG::MeshComponent::~MeshComponent()
{
	destroyRenderTask();
}

void OG::MeshComponent::registerComponent()
{
	PhysicalComponent::registerComponent();
	createRenderTask(owner->getGameInstance()->getRenderer());
	
}

void OG::MeshComponent::createRenderTask(VulkanRenderer* _renderer)
{
	if (mesh_adress >= 0){
		m_model = new ModelRenderObject(_renderer);
		m_model->setMesh(owner->getGameInstance()->getStaticMesh(mesh_adress));
	}
	else {
		std::cout << "trying to create render task for meshcomponent with no assigned staticMesh";
	}
}

void OG::MeshComponent::destroyRenderTask()
{
	if (m_model)
		delete m_model;

	m_model = nullptr;
}

class ModelRenderObject* OG::MeshComponent::getModelRenderObject()
{
	return m_model;
}

void OG::MeshComponent::setStaticMesh(int _mesh_adress)
{
	//task->setMesh(_mesh);
	mesh_adress = _mesh_adress;
	//TODO: recreateRendertask
}

//void OG::MeshComponent::setPosition(const glm::vec3& _pos)
//{
//	PhysicalComponent::setPosition(_pos);
//	task->updateUniformBuffer(transform);
//}

void OG::MeshComponent::update()
{
	PhysicalComponent::update();

	m_model->updateUniformBuffer(transform);
}
