#pragma once

#include <vector>
#include <GL/glew.h>
#include "Model.h"
#include "OmniLight.h"

class Scene;

class Terrain
{
private:
	Scene& m_scene;
	GLfloat* m_yPositions;
	size_t m_width;
	size_t m_height;
	size_t m_xCellsCount;
	size_t m_yCellsCount;
	GLfloat m_cellSize;
	glm::vec2 m_gridSize;
	glm::vec3 m_position;
	glm::vec3 m_baseOffset;
	Model m_terrainModel;
	const Texture* m_texture;
	const OmniLight* m_light;

	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec3> m_colors;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<GLuint> m_indices;

public:
	Terrain(Scene& scene);
	~Terrain();

	void Render(GLfloat dt);

	void CreateRandomTerrain(size_t width, size_t height, GLfloat cellSize, GLfloat maxCellHeightDifference);
	void CreateTerrain(const GLfloat* yPositions, size_t width, size_t height, GLfloat cellSize);
	
	void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const;
	void SetTexture(const Texture* texture);
	void SetLight(const OmniLight* light);
	
	GLfloat GetHeightAt(glm::vec2 position) const;
	glm::vec3 GetNormalAt(glm::vec2 position) const;

private:
	GLfloat GetHeightAtInteger(size_t x, size_t y) const;
	void GenerateCell(size_t x, size_t y);
	void PushTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 aTexCoord, glm::vec2 bTexCoord, glm::vec2 cTexCoord);
};

