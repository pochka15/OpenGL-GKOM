#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "OmniLight.h"
#include "HarvesterBody.h"

class Scene;

class HarvesterChassis
{
private:
	Scene& m_scene;
	const OmniLight* m_light;
	std::vector<Model*> m_allModels;
	Model m_trackLeft;
	Model m_trackRight;
	Model m_wheelsLeft[2];
	Model m_wheelsRight[2];
	Model m_base;
	Model m_leftWheelsBlock;
	Model m_rightWheelsBlock;
	Model m_center;
public:
	HarvesterChassis(Scene& scene);
	~HarvesterChassis();

	glm::mat4 matrix;

	void SetLight(const OmniLight* light);

	void RefreshHarvesterMatrix(const glm::mat4& HarvesterMatrix);
	void Render(GLfloat dt);
};

