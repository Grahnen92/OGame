#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

#include "GLFW/glfw3.h"

class Camera
{
public:
	Camera();
	Camera(float fovy, float aspect_ratio, float z_near, float z_far, glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	Camera(glm::mat4 _transform, glm::mat4 _perspective);
	~Camera();

	void getPosition(glm::vec3& _Position);
	float* getPositionF();
	glm::vec3* getDirection();
	glm::vec3* getUpDirection();

	float* getTransformF();
	glm::mat4* getTransformM();

	float* getPerspectiveF();
	glm::mat4* getPerspectiveM();

	void translate(glm::vec3* _Translation);

	void setPosition(glm::vec3* _Position);

	void setTransform(glm::mat4* _Transform);
	void setPerspective(glm::mat4* _Perspective);
	void setPerspective(float fovy, float aspect_ratio, float z_near, float z_far );

	void update();

	void fpsCamera(GLFWwindow* _window, double _dT);

	float pitch;
	float yaw;

private:

	glm::vec3 position;

	glm::vec3 direction;
	glm::vec3 upDirection;
	glm::vec3 rightDirection;

	glm::mat4 transform;
	glm::mat4 perspective;
};
