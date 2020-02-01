#include "SpatialComponent.h"



OG::SpatialComponent::SpatialComponent()
{
}

OG::SpatialComponent::SpatialComponent(class Actor* _owner) : ActorComponent(_owner)
{
}


OG::SpatialComponent::~SpatialComponent()
{

}

void OG::SpatialComponent::registerComponent()
{
	ActorComponent::registerComponent();

}

void OG::SpatialComponent::update()
{
	ActorComponent::update();
}


void OG::SpatialComponent::getPosition(glm::vec3& _Position)
{
	_Position[0] = transform[4][0];
	_Position[1] = transform[4][1];
	_Position[2] = transform[4][2];
}

float* OG::SpatialComponent::getPositionF()
{
	return &transform[3][0];
}

glm::vec3* OG::SpatialComponent::getPositionV()
{
	return (glm::vec3*)(&transform[3]);
}

void OG::SpatialComponent::setPosition(glm::vec3* _Position)
{
	/*transform[0][3] = (*_Position)[0];
	transform[1][3] = (*_Position)[1];
	transform[2][3] = (*_Position)[2];*/
	transform[3][0] = (*_Position)[0];
	transform[3][1] = (*_Position)[1];
	transform[3][2] = (*_Position)[2];
}

void OG::SpatialComponent::setPosition(const glm::vec3& _Position)
{
	transform[3][0] = _Position[0];
	transform[3][1] = _Position[1];
	transform[3][2] = _Position[2];
	//update();
}

float* OG::SpatialComponent::getTransformF()
{
	return &transform[0][0];
}

glm::mat4* OG::SpatialComponent::getTransformM()
{
	return &transform;
}
void OG::SpatialComponent::setRotation(glm::mat3* _Rotation)
{
	transform[0][0] = (*_Rotation)[0][0];
	transform[0][1] = (*_Rotation)[0][1];
	transform[0][2] = (*_Rotation)[0][2];

	transform[1][0] = (*_Rotation)[1][0];
	transform[1][1] = (*_Rotation)[1][1];
	transform[1][2] = (*_Rotation)[1][2];

	transform[2][0] = (*_Rotation)[2][0];
	transform[2][1] = (*_Rotation)[2][1];
	transform[2][2] = (*_Rotation)[2][2];
}

void OG::SpatialComponent::setRotation(const glm::mat3& _rotation)
{
	transform[0][0] = _rotation[0][0];
	transform[0][1] = _rotation[0][1];
	transform[0][2] = _rotation[0][2];

	transform[1][0] = _rotation[1][0];
	transform[1][1] = _rotation[1][1];
	transform[1][2] = _rotation[1][2];

	transform[2][0] = _rotation[2][0];
	transform[2][1] = _rotation[2][1];
	transform[2][2] = _rotation[2][2];
	//update();
}

void OG::SpatialComponent::setScale(const glm::vec3& _scale)
{
	transform[0][0] = _scale.x;
	transform[1][1] = _scale.y;
	transform[2][2] = _scale.z;
}

void OG::SpatialComponent::setTransform(const glm::mat4& _transform)
{
	transform[0][0] = _transform[0][0];
	transform[0][1] = _transform[0][1];
	transform[0][2] = _transform[0][2];
	transform[0][3] = _transform[0][3];

	transform[1][0] = _transform[1][0];
	transform[1][1] = _transform[1][1];
	transform[1][2] = _transform[1][2];
	transform[1][3] = _transform[1][3];

	transform[2][0] = _transform[2][0];
	transform[2][1] = _transform[2][1];
	transform[2][2] = _transform[2][2];
	transform[2][3] = _transform[2][3];

	transform[3][0] = _transform[3][0];
	transform[3][1] = _transform[3][1];
	transform[3][2] = _transform[3][2];
	transform[3][3] = _transform[3][3];
	//update();
}