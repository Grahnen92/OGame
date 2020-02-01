#pragma once

#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H


#include "OGame/Physics/PhysicalComponent.h"

class VulkanRenderer;
class VkRenderTask;
class StaticMesh;

namespace OG {
	class MeshComponent :
		public PhysicalComponent
	{
	public:
		MeshComponent(Actor* _owner);

		virtual ~MeshComponent();
		virtual void registerComponent();

		class VkRenderTask* getTask();
		void createRenderTask(VulkanRenderer* _renderer);
		void destroyRenderTask();

		void setStaticMesh(int _mesh_adress);


		//void setPosition(const glm::vec3 & _Position) override;

	protected:
		MeshComponent();

		virtual void update();

		VkRenderTask* task = nullptr;
		int mesh_adress = -1;

	private:
		
	};
}


#endif // !MESHCOMPONENT_H
