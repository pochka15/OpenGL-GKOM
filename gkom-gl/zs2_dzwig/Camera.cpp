#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

Camera::Camera(glm::mat4 projection)
	: Camera(projection, glm::vec3(0.0f))
{
}
Camera::Camera(glm::mat4 projection, glm::vec3 position)
	: m_projectionMatrix(projection),
	  m_position(position),
	  m_target(glm::vec3(0.0f)),
	  m_upVector(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Camera::~Camera()
{
}

const glm::vec3 & Camera::GetPosition() const
{
	return m_position;
}

void Camera::SetPosition(const glm::vec3 & position)
{
	m_position = position;
}

const glm::vec3 & Camera::GetTarget() const
{
	return m_target;
}

void Camera::SetTarget(const glm::vec3 & target)
{
	m_target = target;
}

const glm::vec3 & Camera::GetUpVector() const
{
	return m_upVector;
}

void Camera::SetUpVector(const glm::vec3 & upVector)
{
	m_upVector = upVector;
}

glm::mat4 Camera::ComputeViewMatrix() const
{
	return glm::lookAt(m_position, m_target, m_upVector);
}

const glm::mat4 & Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::SetProjectionMatrix(const glm::mat4 & projection)
{
	m_projectionMatrix = projection;
}
