#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "HarvesterChassis.h"
#include "OmniLight.h"

class Scene;

class Harvester
{
private:
	Scene& m_scene;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	float m_speed;
	float m_rotationSpeed;
	HarvesterChassis m_chassis;
	const OmniLight* m_light;

	glm::vec3 m_body_rotation;
	glm::vec3 m_beam_rotation;
	HarvesterBeam m_beam;
	
	HarvesterBody m_body;
public:
	Harvester(Scene& scene);
	~Harvester();

	void Update(GLfloat dt);
	void Render(GLfloat dt);

	void SetLight(const OmniLight* light);

	void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const;
	GLfloat GetDirection() const;

private:
	bool IsTurnLeftPressed() const;
	bool IsTurnRightPressed() const;
	bool IsForwardPressed() const;
	bool IsReversePressed() const;

	bool IsRotateBodyRightPressed() const;
	bool IsRotateBodyLeftPressed() const;
	bool IsRotateBeamUpPressed() const;
	bool IsRotateBeamDownPressed() const;

	void UpdateTilt();
	glm::mat4 ComputeHarvesterMatrix() const;
	glm::mat4 ComputeBodyMatrix() const;
	glm::mat4 ComputeBeamMatrix() const;
};

