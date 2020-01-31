#include "FlyingCameraController.h"

#include <glm/gtc/constants.hpp>

FlyingCameraController::FlyingCameraController(Camera& camera)
	: m_camera(camera),
	m_cameraAngle(5 * glm::pi<GLfloat>() / 4, 0),
	m_cameraSpeed(1.5f),
	m_observerSpeed(3)
{
}


FlyingCameraController::~FlyingCameraController()
{
}

void FlyingCameraController::UpdateDirection(GLfloat dt, glm::vec2 delta)
{
	glm::vec3 camPos = m_camera.GetPosition();
	glm::vec3 camTar = m_camera.GetTarget();

	m_cameraAngle += delta * m_cameraSpeed * dt;
	m_cameraAngle.x = glm::mod(m_cameraAngle.x, glm::two_pi<GLfloat>());
	if (m_cameraAngle.y <= -glm::half_pi<GLfloat>())
	{
		m_cameraAngle.y = -glm::half_pi<GLfloat>() + 0.01f;
	}
	else if (m_cameraAngle.y >= glm::half_pi<GLfloat>())
	{
		m_cameraAngle.y = glm::half_pi<GLfloat>() - 0.01f;
	}

	// radius = 1
	camTar.x = camPos.x + glm::cos(m_cameraAngle.x) * glm::cos(m_cameraAngle.y);
	camTar.z = camPos.z + glm::sin(m_cameraAngle.x) * glm::cos(m_cameraAngle.y);
	camTar.y = camPos.y + -glm::sin(m_cameraAngle.y);

	m_camera.SetTarget(camTar);
}

void FlyingCameraController::UpdatePosition(GLfloat dt, bool front, bool back, bool left, bool right, bool up, bool down)
{
	glm::vec3 camPos = m_camera.GetPosition();
	glm::vec3 camTar = m_camera.GetTarget();

	GLfloat moveAngle = m_cameraAngle.x;
	bool moveOnPlane = false;
	if (left)
	{
		moveOnPlane = true;
		moveAngle = m_cameraAngle.x - glm::half_pi<GLfloat>();

		if (back) moveAngle -= glm::quarter_pi<GLfloat>();
		if (front) moveAngle += glm::quarter_pi<GLfloat>();
		if (right) moveOnPlane = false;
	}
	else if (right)
	{
		moveOnPlane = true;
		moveAngle = m_cameraAngle.x + glm::half_pi<GLfloat>();

		if (back) moveAngle += glm::quarter_pi<GLfloat>();
		if (front) moveAngle -= glm::quarter_pi<GLfloat>();
	}
	else if (front)
	{
		moveOnPlane = true;
		if (back) moveOnPlane = false;
	}
	else if (back)
	{
		moveOnPlane = true;
		moveAngle = m_cameraAngle.x - glm::pi<GLfloat>();
	}

	int moveYDirection = 0;
	if (down)
	{
		moveYDirection = -1;
		if (up) moveYDirection = 0;
	}
	else if (up)
	{
		moveYDirection = 1;
	}

	glm::vec3 cameraStep(moveOnPlane ? glm::cos(moveAngle) : 0, moveYDirection, moveOnPlane ? glm::sin(moveAngle) : 0);
	cameraStep *= m_observerSpeed * dt;
	camPos += cameraStep;
	camTar += cameraStep;

	m_camera.SetPosition(camPos);
	m_camera.SetTarget(camTar);
}
