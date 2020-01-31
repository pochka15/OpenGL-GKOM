#include "Scene.h"

#include <cstdlib>
#include <vector>
#include <glm/gtc/constants.hpp>
#include "ModelGenerator.h"

#include <iostream>

Scene::Scene(GLFWwindow* window, glm::mat4 projection)
	: m_window(window),
	m_camera(projection), m_cameraScroll(0), m_cameraScrollSpeed(2), m_firstPersonCamera(false), m_flyingCamera(m_camera),
	m_light(glm::vec3(), glm::vec3(1), 40), m_terrainLight(glm::vec3(), glm::vec3(1), 150),
	m_terrain(*this), m_Harvester(*this),
	m_grassTexture("tough_grass.png")
{
	SetupCursor();

	glm::vec3 centerPos(100, 0, 100);

	m_terrainLight.SetSpecularColor(glm::vec3(0));

	m_terrain.CreateRandomTerrain(50, 50, 2.5f, 0.2f);
	m_terrain.SetPosition(centerPos);
	m_terrain.SetTexture(&m_grassTexture);
	m_terrain.SetLight(&m_terrainLight);
	
	m_Harvester.SetPosition(centerPos);
	m_Harvester.SetLight(&m_light);
	m_Harvester.Update(0); // make the Harvester "land" on the terrain
	
	m_camera.SetPosition(m_Harvester.GetPosition() + glm::vec3(4, 1.5f, 4));
	m_camera.SetTarget(m_Harvester.GetPosition());
}

Scene::~Scene()
{
}

void Scene::Update(GLfloat dt)
{
	UpdateCamera(dt);

	const glm::vec3 HarvesterPos = m_Harvester.GetPosition();
	m_light.SetPosition(glm::vec3(HarvesterPos.x, HarvesterPos.y + 7.5, HarvesterPos.z - 0.5f));
	m_terrainLight.SetPosition(glm::vec3(HarvesterPos.x, m_terrain.GetHeightAt(glm::vec2(HarvesterPos.x, HarvesterPos.z)) + 15, HarvesterPos.z));

	m_Harvester.Update(dt);
}

void Scene::Render(GLfloat dt)
{
	m_terrain.Render(dt);

	m_Harvester.Render(dt);
}

void Scene::KeyCallback(int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		{
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}
		else
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	else if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		m_firstPersonCamera = !m_firstPersonCamera;
	}
}

void Scene::MouseCallback(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}

void Scene::ScrollCallback(double xOffset, double yOffset)
{
	if (yOffset != 0)
	{
		m_cameraScroll += (yOffset > 0 ? 1 : -1) * m_cameraScrollSpeed;
	}
}

const Camera & Scene::GetCamera() const
{
	return m_camera;
}

const BasicShader & Scene::GetBasicShader() const
{
	return m_basicShader;
}

const TextureShader & Scene::GetTextureShader() const
{
	return m_textureShader;
}

const LightShader & Scene::GetLightShader() const
{
	return m_lightShader;
}

const TextureLightShader & Scene::GetTextureLightShader() const
{
	return m_textureLightShader;
}

const Terrain & Scene::GetTerrain() const
{
	return m_terrain;
}

bool Scene::IsKeyPressed(int key)
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Scene::IsFirstPersonCameraEnabled() const
{
	return m_firstPersonCamera;
}

void Scene::UpdateCamera(GLfloat dt)
{
	if (m_firstPersonCamera)
	{
		m_camera.SetPosition(m_Harvester.GetPosition() + glm::vec3(0, 2.5f, 0));
	}
	else
	{
		m_flyingCamera.UpdatePosition(dt,
			IsKeyPressed(GLFW_KEY_W),
			IsKeyPressed(GLFW_KEY_S),
			IsKeyPressed(GLFW_KEY_A),
			IsKeyPressed(GLFW_KEY_D),
			IsKeyPressed(GLFW_KEY_E) || m_cameraScroll > 0,
			IsKeyPressed(GLFW_KEY_Q) || m_cameraScroll < 0);
	}

	if (glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_HIDDEN)
	{
		glm::dvec2 cursorPos;
		glm::ivec2 winSize;
		glfwGetWindowSize(m_window, &winSize.x, &winSize.y);

		glfwGetCursorPos(m_window, &cursorPos.x, &cursorPos.y);
		glfwSetCursorPos(m_window, winSize.x / 2, winSize.y / 2);

		glm::vec2 delta = cursorPos - glm::dvec2(winSize.x / 2, winSize.y / 2);
		m_flyingCamera.UpdateDirection(dt, delta);
	}

	if (m_cameraScroll != 0) m_cameraScroll += m_cameraScroll > 0 ? -1 : 1;
}

void Scene::SetupCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glm::ivec2 winSize;
	glfwGetWindowSize(m_window, &winSize.x, &winSize.y);
	glfwSetCursorPos(m_window, winSize.x / 2, winSize.y / 2);
}
