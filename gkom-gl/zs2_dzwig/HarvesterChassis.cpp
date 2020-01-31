#include "HarvesterChassis.h"

#include <glm/gtc/constants.hpp>
#include "ModelGenerator.h"
#include "Scene.h"

HarvesterChassis::HarvesterChassis(Scene & scene)
	: m_scene(scene)
{
	m_allModels.push_back(&m_trackLeft);
	m_allModels.push_back(&m_trackRight);
	m_allModels.push_back(&m_wheelsRight[0]);
	m_allModels.push_back(&m_wheelsRight[1]);
	m_allModels.push_back(&m_wheelsLeft[0]);
	m_allModels.push_back(&m_wheelsLeft[1]);
	m_allModels.push_back(&m_base);
	m_allModels.push_back(&m_rightWheelsBlock);
	m_allModels.push_back(&m_leftWheelsBlock);
	m_allModels.push_back(&m_center);

	ModelGenerator::ChassisTrack(m_trackLeft, glm::vec3(0.25f, 0.25f, 1.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	m_trackLeft.SetPosition(glm::vec3(0.5f, 0, 0));

	ModelGenerator::ChassisTrack(m_trackRight, glm::vec3(0.25f, 0.25f, 1.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	m_trackRight.SetPosition(glm::vec3(-0.5f, 0, 0));

	ModelGenerator::Cylinder(m_wheelsLeft[0], 0.25f, 0.1f, glm::vec3(0.2f));
	m_wheelsRight[0].SetPosition(glm::vec3(0.525f, 0.125f, 0.625f));
	m_wheelsRight[0].SetRotation(glm::vec3(0, 0, glm::pi<GLfloat>() / 2));

	ModelGenerator::Cylinder(m_wheelsLeft[1], 0.25f, 0.1f, glm::vec3(0.2f));
	m_wheelsRight[1].SetPosition(glm::vec3(0.525f, 0.125f, -0.625f));
	m_wheelsRight[1].SetRotation(glm::vec3(0, 0, glm::pi<GLfloat>() / 2));

	ModelGenerator::Cylinder(m_wheelsRight[0], 0.25f, 0.1f, glm::vec3(0.2f));
	m_wheelsLeft[0].SetPosition(glm::vec3(-0.525f, 0.125f, 0.625f));
	m_wheelsLeft[0].SetRotation(glm::vec3(0, 0, glm::pi<GLfloat>() / 2));

	ModelGenerator::Cylinder(m_wheelsRight[1], 0.25f, 0.1f, glm::vec3(0.2f));
	m_wheelsLeft[1].SetPosition(glm::vec3(-0.525f, 0.125f, -0.625f));
	m_wheelsLeft[1].SetRotation(glm::vec3(0, 0, glm::pi<GLfloat>() / 2));

	ModelGenerator::Cuboid(m_base, glm::vec3(1.0f, 0.15f, 1), glm::vec3(0.5f, 0.5f, 0.5f));
	m_base.SetPosition(glm::vec3(0, 0.125f, 0));

	ModelGenerator::Cuboid(m_rightWheelsBlock, glm::vec3(0.25f, 0.15f, 1.0f), glm::vec3(0.2f));
	m_rightWheelsBlock.SetPosition(glm::vec3(0.55f, 0.125f, 0.0f));

	ModelGenerator::Cuboid(m_leftWheelsBlock, glm::vec3(0.25f, 0.15f, 1.0f), glm::vec3(0.2f));
	m_leftWheelsBlock.SetPosition(glm::vec3(-0.55f, 0.125f, 0.0f));

	ModelGenerator::Cylinder(m_center, 0.2f, 0.25f, glm::vec3(0.5f));
	m_center.SetPosition(glm::vec3(0, 0.25f, 0));
}

HarvesterChassis::~HarvesterChassis()
{
}

void HarvesterChassis::SetLight(const OmniLight * light)
{
	m_light = light;
}

void HarvesterChassis::RefreshHarvesterMatrix(const glm::mat4& HarvesterMatrix)
{
	matrix = HarvesterMatrix;
	for (auto model : m_allModels) model->SetAdditionalTransformation(HarvesterMatrix);
}

void HarvesterChassis::Render(GLfloat dt)
{
	for (auto model : m_allModels)
	{
		m_scene.GetLightShader().Render(*model, m_scene.GetCamera(), *m_light);
	}
}
