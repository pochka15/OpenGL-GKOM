#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Camera.h"

class FlyingCameraController
{
private:
	Camera& m_camera;
	glm::vec2 m_cameraAngle;
	GLfloat m_cameraSpeed;
	GLfloat m_observerSpeed;

public:
	FlyingCameraController(Camera& camera);
	~FlyingCameraController();

	void UpdateDirection(GLfloat dt, glm::vec2 delta);
	void UpdatePosition(GLfloat dt, bool front, bool back, bool left, bool right, bool up, bool down);
};

