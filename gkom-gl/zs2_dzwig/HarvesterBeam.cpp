#include "HarvesterBeam.h"
#include "Scene.h"
#include "ModelGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

HarvesterBeam::HarvesterBeam(Scene& scene):m_scene(scene) {
	ModelGenerator::Cuboid(m_stick1, glm::vec3(0.1f, 2.0f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f));
	m_stick1.SetPosition(glm::vec3(0.95f, 1.0f, 0.0f));//

	ModelGenerator::Cuboid(m_stick2, glm::vec3(0.1f, 1.0f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f));
	m_stick2.SetPosition(glm::vec3(0.95f, 2.0f, -0.5f));//-0.5
	m_stick2.SetRotation(glm::vec3(1.55f, 1.6f, M_PI_2));

	ModelGenerator::Cylinder(m_cyl, 0.125f, 0.15f, glm::vec3(0.5f, 0.5f, 0.5f));
	m_cyl.SetPosition(glm::vec3(0.95f, 2.0f, 0.0f));//0.0
	m_cyl.SetRotation(glm::vec3(0.0f, 0.0f, M_PI_2));
}

HarvesterBeam::~HarvesterBeam() {
}

void HarvesterBeam::SetLight(const OmniLight* light) 
{
	m_light = light;
}

void HarvesterBeam::RefreshMatrices(const glm::mat4& HarvesterBodyMatrix) 
{
	m_stick1.SetAdditionalTransformation(HarvesterBodyMatrix);
	m_stick2.SetAdditionalTransformation(HarvesterBodyMatrix);
	m_cyl.SetAdditionalTransformation(HarvesterBodyMatrix);
}

void HarvesterBeam::Render(GLfloat dt) 
{
	m_scene.GetLightShader().Render(m_stick1, m_scene.GetCamera(), *m_light);
	m_scene.GetLightShader().Render(m_stick2, m_scene.GetCamera(), *m_light);
	m_scene.GetLightShader().Render(m_cyl, m_scene.GetCamera(), *m_light);
}