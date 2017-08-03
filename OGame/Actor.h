#pragma once
#ifndef  ACTOR_H
#define ACTOR_H

#include "Entity.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace OG {

	class ActorComponent;
	class SpatialComponent;

	class Actor :
		public Entity
	{

		friend class GameInstance;
	public:
		
		Actor(GameInstance* _gi);

		virtual ~Actor();

		template<class C>
		C* createDefaultComponent() {
			C* component = new C(this);
			components.push_back(component);
			return component;
		}

		//TODO: look into code smell
		template<class C>
		C* findFirstComponentOfClass() {
			for (const auto & component : components)
			{
				C* comp_test = dynamic_cast<C*>(component);
				if (comp_test)
					return comp_test;
			}
			return nullptr;
		}

		ActorComponent* findComponent(ActorComponent* _component);
		bool removeComponent(ActorComponent* _component);

		bool setTransform(const glm::mat4& _transform);
		bool setPosition(const glm::vec3& _position);
		bool setRotation(const glm::vec3& _rotation);
		bool setScale(const glm::vec3& _scale);

	protected:
		Actor();

		OG::SpatialComponent* root_component = nullptr;

		std::vector<ActorComponent*> components;

		virtual void update(float delta_time);

	private:

		
	};
}


#endif // ! ACTOR_H

 


