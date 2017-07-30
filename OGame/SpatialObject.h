#pragma once
#include "Entity.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpatialObject :
	public Entity
{
public:

	//() ;
	virtual ~SpatialObject() {}

	void getPosition(glm::vec3& _Position);
	float* getPositionF();
	glm::vec3* getPositionV();
	void setPosition(glm::vec3* _Position);
	virtual void setPosition(const glm::vec3& _Position);

	void setRotation(glm::mat3* _Rotation);

	void setScale(const glm::vec3& _scale);

	float* getTransformF();
	glm::mat4* getTransformM();
	void setTransform(const glm::mat4& _transform);

	void update() {}

protected:

	glm::mat4 transform;
};

