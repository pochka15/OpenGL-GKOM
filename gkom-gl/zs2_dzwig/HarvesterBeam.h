#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "OmniLight.h"

class Scene;

class HarvesterBeam
{
private:
	Scene& m_scene;

	const OmniLight* m_light;

	Model m_stick1; // Cube
	Model m_stick2; // Cube
	Model m_cyl; // Cylinder

public:
	HarvesterBeam(Scene& scene);
	~HarvesterBeam();

	void SetLight(const OmniLight* light);

	void RefreshMatrices(const glm::mat4& HarvesterBodyMatrix);
	void Render(GLfloat dt);
};