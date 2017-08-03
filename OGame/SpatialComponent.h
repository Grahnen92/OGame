#pragma once

#ifndef SPATIALCOMPONENT_H
#define SPATIALCOMPONENT_H


#include "ActorComponent.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OG {

	class SpatialComponent :
		public ActorComponent
	{
	public:
		SpatialComponent(Actor* _owner);
		
		virtual ~SpatialComponent();

		virtual void registerComponent();

		void getPosition(glm::vec3& _Position);
		float* getPositionF();
		glm::vec3* getPositionV();
		void setPosition(glm::vec3* _Position);
		virtual void setPosition(const glm::vec3& _Position);

		void setRotation(glm::mat3* _Rotation);
		virtual void setRotation(const glm::mat3& _rotation);

		void setScale(const glm::vec3& _scale);

		float* getTransformF();
		glm::mat4* getTransformM();
		virtual void setTransform(const glm::mat4& _transform);

		

	protected:
		SpatialComponent();

		virtual void update();

		glm::mat4 transform;

	private:
		
	};

}
#endif // !SPATIALCOMPONENT_H