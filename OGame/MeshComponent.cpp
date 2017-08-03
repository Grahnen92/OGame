#include "MeshComponent.h"
#include "VkRenderTask.h"
#include "StaticMesh.h"
#include "Actor.h"
#include "GameInstance.h"


OG::MeshComponent::MeshComponent() : mesh_adress(-1), task(nullptr)
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
		task = new VkRenderTask(_renderer);
		task->setMesh(owner->getGameInstance()->getStaticMesh(mesh_adress));
	}
	else {
		std::cout << "trying to create render task for meshcomponent with no assigned staticMesh";
	}
}

void OG::MeshComponent::destroyRenderTask()
{
	if (task)
		delete task;

	task = nullptr;
}

class VkRenderTask* OG::MeshComponent::getTask()
{
	return task;
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

	task->updateUniformBuffer(transform);
}
