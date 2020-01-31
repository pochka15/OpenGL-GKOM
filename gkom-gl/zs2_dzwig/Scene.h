#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Model.h"
#include "BasicShader.h"
#include "LightShader.h"
#include "Texture.h"
#include "OmniLight.h"
#include "Harvester.h"
#include "Texture.h"
#include "TextureShader.h"
#include "FlyingCameraController.h"
#include "Terrain.h"
#include "TextureLightShader.h"

class Scene
{
private:
	GLFWwindow* m_window;
	Camera m_camera;
	int m_cameraScroll;
	int m_cameraScrollSpeed;
	bool m_firstPersonCamera;

	BasicShader m_basicShader;
	TextureShader m_textureShader;
	LightShader m_lightShader;
	TextureLightShader m_textureLightShader;
	
	OmniLight m_light;
	OmniLight m_terrainLight;

	Terrain m_terrain;
	Harvester m_Harvester;
	
	Texture m_grassTexture;
	
	FlyingCameraController m_flyingCamera;

public:
	Scene(GLFWwindow* window, glm::mat4 projection);
	~Scene();

	void Update(GLfloat dt);
	void Render(GLfloat dt);

	void KeyCallback(int key, int scancode, int action, int mode);
	void MouseCallback(int button, int action, int mods);
	void ScrollCallback(double xOffset, double yOffset);

	const Camera& GetCamera() const;
	const BasicShader& GetBasicShader() const;
	const TextureShader& GetTextureShader() const;
	const LightShader& GetLightShader() const;
	const TextureLightShader& GetTextureLightShader() const;
	const Terrain& GetTerrain() const;

	bool IsKeyPressed(int key);
	bool IsFirstPersonCameraEnabled() const;

private:
	void UpdateCamera(GLfloat dt);
	void SetupCursor();
};

