#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "OmniLight.h"
#include "HarvesterBeam.h"

class Scene;

class HarvesterBody 
{
private:
	Scene& m_scene;
	const OmniLight* m_light;

	Model m_base; // Cube
	Model m_supporter; //Cube
	Model m_cabin; // Trapezioid
	Model m_wheel1; // Cylinder
	Model m_wheel2; // Cylinder


public:
	HarvesterBody(Scene& scene);
	~HarvesterBody();

	glm::mat4 matrix;

	void SetLight(const OmniLight* light);

	void RefreshMatrices(const glm::mat4& HarvesterMatrix);
	void Render(GLfloat dt);
};