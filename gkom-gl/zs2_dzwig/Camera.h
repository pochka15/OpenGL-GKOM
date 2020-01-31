#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_upVector;

	glm::mat4 m_projectionMatrix;

public:
	Camera(glm::mat4 projection);
	Camera(glm::mat4 projection, glm::vec3 position);
	~Camera();

	const glm::vec3& GetPosition() const;
	void SetPosition(const glm::vec3& position);

	const glm::vec3& GetTarget() const;
	void SetTarget(const glm::vec3& target);

	const glm::vec3& GetUpVector() const;
	void SetUpVector(const glm::vec3& upVector);

	glm::mat4 ComputeViewMatrix() const;

	const glm::mat4& GetProjectionMatrix() const;
	void SetProjectionMatrix(const glm::mat4& projection);
};

