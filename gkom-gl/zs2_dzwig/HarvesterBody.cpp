#include "HarvesterBody.h"
#include "ModelGenerator.h"
#include "Scene.h"
#define _USE_MATH_DEFINES
#include <math.h>

HarvesterBody::HarvesterBody(Scene& scene):m_scene(scene) 
{
	ModelGenerator::Cuboid(m_base, glm::vec3(1.0f, 0.5f, 1.75f), glm::vec3(0.2f, 0.4f, 0.0f));
	m_base.SetPosition(glm::vec3(0.0f, 0.6f, 0.2f));

	ModelGenerator::Cuboid(m_supporter, glm::vec3(0.5f, 0.1f, 1.5f), glm::vec3(0.0f, 1.0f, 1.0f));
	m_supporter.SetPosition(glm::vec3(0.0f, 0.3f, -1.0f));

	ModelGenerator::Trapezioid(m_cabin, 1.0f, 0.2f, glm::vec3(0.6f, 0.8f, 0.5f), glm::vec3(0.50f, 0.2f, 0.1f));
	m_cabin.SetPosition(glm::vec3(0.0f, 0.7f, -1.2f));
	m_cabin.SetRotation(glm::vec3(0, M_PI_2, 0.0f));

	ModelGenerator::Cylinder(m_wheel1, 0.125f, 0.35f, glm::vec3(0.5f, 0.5f, 0.5f));
	m_wheel1.SetPosition(glm::vec3(0.3f, 0.25f, -1.2f));
	m_wheel1.SetRotation(glm::vec3(0.0f, 0.0f, M_PI_2));

	ModelGenerator::Cylinder(m_wheel2, 0.125f, 0.35f, glm::vec3(0.5f, 0.5f, 0.5f));
	m_wheel2.SetPosition(glm::vec3(-0.3f, 0.25f, -1.2f));
	m_wheel2.SetRotation(glm::vec3(0.0f, 0.0f, M_PI_2));
}

HarvesterBody::~HarvesterBody() 
{
}

void HarvesterBody::SetLight(const OmniLight* light) 
{
	m_light = light;
}

void HarvesterBody::RefreshMatrices(const glm::mat4& HarvesterMatrix) 
{
	m_base.SetAdditionalTransformation(HarvesterMatrix);
	m_supporter.SetAdditionalTransformation(HarvesterMatrix);
	m_cabin.SetAdditionalTransformation(HarvesterMatrix);
	m_wheel1.SetAdditionalTransformation(HarvesterMatrix);
	m_wheel2.SetAdditionalTransformation(HarvesterMatrix);
}

void HarvesterBody::Render(GLfloat dt) {
	m_scene.GetLightShader().Render(m_base, m_scene.GetCamera(), *m_light);
	m_scene.GetLightShader().Render(m_supporter, m_scene.GetCamera(), *m_light);
	m_scene.GetLightShader().Render(m_cabin, m_scene.GetCamera(), *m_light);
	m_scene.GetLightShader().Render(m_wheel1, m_scene.GetCamera(), *m_light);
	m_scene.GetLightShader().Render(m_wheel2, m_scene.GetCamera(), *m_light);
}