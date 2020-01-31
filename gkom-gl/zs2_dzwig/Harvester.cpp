#include "Harvester.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "ModelGenerator.h"
#include "Scene.h"
#include "Terrain.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

Harvester::Harvester(Scene & scene)
	: m_scene(scene), m_chassis(scene),
	m_speed(1), m_rotationSpeed(glm::quarter_pi<float>()),
	m_body(scene), m_beam(scene)
{
}

Harvester::~Harvester()
{
}

void Harvester::Update(GLfloat dt)
{
	if (IsTurnLeftPressed()) m_rotation.y += m_rotationSpeed * dt;
	if (IsTurnRightPressed()) m_rotation.y -= m_rotationSpeed * dt;
	if (IsForwardPressed())
	{
		m_position.x += glm::sin(m_rotation.y) * m_speed * dt;
		m_position.z += glm::cos(m_rotation.y) * m_speed * dt;
	}
	if (IsReversePressed())
	{
		m_position.x -= glm::sin(m_rotation.y) * m_speed * dt;
		m_position.z -= glm::cos(m_rotation.y) * m_speed * dt;
	}

	if (IsRotateBeamUpPressed()) {
		m_beam_rotation.x += m_rotationSpeed * dt;
		if (m_beam_rotation.x >= (M_PI/3)) {
			m_beam_rotation.x = (M_PI/3);
		}
	}
	if (IsRotateBeamDownPressed()) {
		m_beam_rotation.x -= m_rotationSpeed * dt;
		if (m_beam_rotation.x <= 0.0f)
			m_beam_rotation.x = 0.0f;
	}

	UpdateTilt();

	glm::mat4 HarvesterMatrix = ComputeHarvesterMatrix();
	m_chassis.RefreshHarvesterMatrix(HarvesterMatrix);
	glm::mat4 bodyMatrix = HarvesterMatrix * ComputeBodyMatrix();
	glm::mat4 beamMatrix = bodyMatrix * ComputeBeamMatrix();

	m_body.RefreshMatrices(bodyMatrix);
	m_beam.RefreshMatrices(beamMatrix);

}

void Harvester::Render(GLfloat dt)
{
	m_chassis.Render(dt);
	m_body.Render(dt);
	m_beam.Render(dt);

}

void Harvester::SetLight(const OmniLight * light)
{
	m_light = light;
	m_chassis.SetLight(light);
	m_body.SetLight(light);
	m_beam.SetLight(light);
}

void Harvester::SetPosition(const glm::vec3 & position)
{
	m_position = position;
}

const glm::vec3 & Harvester::GetPosition() const
{
	return m_position;
}

GLfloat Harvester::GetDirection() const
{
	return m_rotation.y;
}

bool Harvester::IsTurnLeftPressed() const
{
	return m_scene.IsKeyPressed(GLFW_KEY_LEFT) ||
		(m_scene.IsFirstPersonCameraEnabled() && m_scene.IsKeyPressed(GLFW_KEY_A));
}

bool Harvester::IsTurnRightPressed() const
{
	return m_scene.IsKeyPressed(GLFW_KEY_RIGHT) ||
		(m_scene.IsFirstPersonCameraEnabled() && m_scene.IsKeyPressed(GLFW_KEY_D));
}

bool Harvester::IsForwardPressed() const
{
	return m_scene.IsKeyPressed(GLFW_KEY_UP) ||
		(m_scene.IsFirstPersonCameraEnabled() && m_scene.IsKeyPressed(GLFW_KEY_W));
}

bool Harvester::IsRotateBeamUpPressed() const  
{
	return m_scene.IsKeyPressed(GLFW_KEY_I);
}

bool Harvester::IsRotateBeamDownPressed() const  
{
	return m_scene.IsKeyPressed(GLFW_KEY_K);
}


bool Harvester::IsReversePressed() const
{
	return m_scene.IsKeyPressed(GLFW_KEY_DOWN) ||
		(m_scene.IsFirstPersonCameraEnabled() && m_scene.IsKeyPressed(GLFW_KEY_S));
}

void Harvester::UpdateTilt()
{
	const Terrain& terrain = m_scene.GetTerrain();

	glm::mat4 matrix = glm::translate(m_position) * glm::rotate(m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 fr = matrix * glm::vec4(-0.5f, 0, 0.75f, 1);
	glm::vec4 fl = matrix * glm::vec4(0.5f, 0, 0.75f, 1);
	glm::vec4 rr = matrix * glm::vec4(-0.5f, 0, -0.75f, 1);
	glm::vec4 rl = matrix * glm::vec4(0.5f, 0, -0.75f, 1);
	
	GLfloat frontRightH = terrain.GetHeightAt(glm::vec2(fr.x, fr.z));
	GLfloat frontLeftH = terrain.GetHeightAt(glm::vec2(fl.x, fl.z));
	GLfloat rearRightH = terrain.GetHeightAt(glm::vec2(rr.x, rr.z));
	GLfloat rearLeftH = terrain.GetHeightAt(glm::vec2(rl.x, rl.z));

	glm::vec3 frontLeftPos(fl.x, frontLeftH, fl.z);
	glm::vec3 frontRightPos(fr.x, frontRightH, fr.z);
	glm::vec3 rearRightPos(rr.x, rearRightH, rr.z);
	glm::vec3 rearLeftPos(rl.x, rearLeftH, rl.z);

	glm::vec3 normal = glm::normalize(
		rearRightH > frontLeftH ?
		glm::cross(frontRightPos - rearRightPos, rearLeftPos - rearRightPos) :
		glm::cross(rearLeftPos - frontLeftPos, frontRightPos - frontLeftPos));

	glm::vec2 centerPos(m_position.x, m_position.z);

	m_rotation.x = glm::orientedAngle(glm::normalize(glm::vec2(normal.z, normal.y)), glm::vec2(0, 1));
	m_rotation.z = glm::orientedAngle(glm::normalize(glm::vec2(normal.x, normal.y)), glm::vec2(0, 1));

	m_position.y = terrain.GetHeightAt(centerPos);
}

glm::mat4 Harvester::ComputeHarvesterMatrix() const
{
	return
		glm::translate(m_position) *
		glm::rotate(m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate((float)(m_rotation.y + M_PI), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Harvester::ComputeBodyMatrix() const
{
	return
		glm::rotate(m_body_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(m_body_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_body_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Harvester::ComputeBeamMatrix() const
{
	return
		glm::translate(glm::vec3(-0.95f,0.25f,-1.5f)) * 
		glm::rotate(m_beam_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(-m_beam_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_beam_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
}