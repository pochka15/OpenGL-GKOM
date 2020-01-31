#include "Terrain.h"

#include "ModelGenerator.h"
#include "Scene.h"

Terrain::Terrain(Scene& scene)
	: m_scene(scene), m_yPositions(nullptr)
{
}

Terrain::~Terrain()
{
}

void Terrain::Render(GLfloat dt)
{
	m_scene.GetTextureLightShader().Render(m_terrainModel, m_scene.GetCamera(), *m_texture, *m_light);
}

void Terrain::CreateRandomTerrain(size_t width, size_t height, GLfloat cellSize, GLfloat maxCellHeightDifference)
{
	GLfloat prev = 0;
	std::vector<GLfloat> heights;
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			prev += static_cast<float>(rand() % 10000 - 5000) * (maxCellHeightDifference / 10000.0f);
			heights.push_back(prev);
		}
	}

	CreateTerrain(heights.data(), width, height, cellSize);
}

void Terrain::CreateTerrain(const GLfloat* yPositions, size_t width, size_t height, GLfloat cellSize)
{
	m_yPositions = new GLfloat[width * height];
	std::copy(yPositions, yPositions + width * height, m_yPositions);
	m_width = width;
	m_height = height;
	m_cellSize = cellSize;
	m_xCellsCount = width - 1;
	m_yCellsCount = height - 1;
	m_gridSize = glm::vec2(m_xCellsCount, m_yCellsCount) * m_cellSize;

	for (size_t y = 0; y < m_yCellsCount; y++)
	{
		for (size_t x = 0; x < m_xCellsCount; x++)
		{
			GenerateCell(x, y);
		}
	}

	m_terrainModel.PositionData(m_positions.data(), m_positions.size());
	m_terrainModel.ColorData(m_colors.data(), m_colors.size());
	m_terrainModel.TexCoordsData(m_texCoords.data(), m_texCoords.size());
	m_terrainModel.NormalData(m_normals.data(), m_normals.size());
	m_terrainModel.IndexData(m_indices.data(), m_indices.size());
}

void Terrain::SetPosition(const glm::vec3 & position)
{
	m_position = position;
	m_baseOffset = glm::vec3(m_position.x - m_gridSize.x / 2, m_position.y, m_position.z - m_gridSize.y / 2);
	m_terrainModel.SetPosition(m_baseOffset);
}

const glm::vec3 & Terrain::GetPosition() const
{
	return m_position;
}

void Terrain::SetTexture(const Texture* texture)
{
	m_texture = texture;
}

void Terrain::SetLight(const OmniLight * light)
{
	m_light = light;
}

GLfloat Terrain::GetHeightAt(glm::vec2 position) const
{
	glm::vec2 gridPos = position - glm::vec2(m_position.x, m_position.z) + m_gridSize / 2.0f;
	gridPos /= m_cellSize;

	glm::vec2 lowPos = glm::clamp(glm::floor(gridPos), glm::vec2(0), glm::vec2(m_width, m_height));
	glm::vec2 highPos = glm::clamp(glm::ceil(gridPos), glm::vec2(0), glm::vec2(m_width, m_height));

	glm::vec2 factors = gridPos - lowPos;

	GLfloat tlH = GetHeightAtInteger(static_cast<size_t>(highPos.x), static_cast<size_t>(highPos.y));
	GLfloat trH = GetHeightAtInteger(static_cast<size_t>(lowPos.x), static_cast<size_t>(highPos.y));
	GLfloat brH = GetHeightAtInteger(static_cast<size_t>(lowPos.x), static_cast<size_t>(lowPos.y));
	GLfloat blH = GetHeightAtInteger(static_cast<size_t>(highPos.x), static_cast<size_t>(lowPos.y));

	GLfloat topH = tlH * factors.x + trH * (1 - factors.x);
	GLfloat bottomH = blH * factors.x + brH * (1 - factors.x);

	return topH * factors.y + bottomH * (1 - factors.y);
}

glm::vec3 Terrain::GetNormalAt(glm::vec2 position) const
{
	glm::vec2 gridPos = position - glm::vec2(m_position.x, m_position.z) + m_gridSize / 2.0f;
	gridPos /= m_cellSize;

	glm::vec2 lowPos = glm::clamp(glm::floor(gridPos), glm::vec2(0), glm::vec2(m_width, m_height));
	glm::vec2 highPos = glm::clamp(glm::ceil(gridPos), glm::vec2(0), glm::vec2(m_width, m_height));

	if (lowPos.x == highPos.x)
	{
		highPos.x += 1;
		if (highPos.x > m_gridSize.x)
		{
			highPos.x -= 1;
			lowPos.x -= 1;
		}
	}
	if (lowPos.y == highPos.y)
	{
		highPos.y += 1;
		if (highPos.y > m_gridSize.y)
		{
			highPos.y -= 1;
			lowPos.y -= 1;
		}
	}

	GLfloat tlH = GetHeightAtInteger(static_cast<size_t>(highPos.x), static_cast<size_t>(highPos.y));
	GLfloat trH = GetHeightAtInteger(static_cast<size_t>(lowPos.x), static_cast<size_t>(highPos.y));
	GLfloat brH = GetHeightAtInteger(static_cast<size_t>(lowPos.x), static_cast<size_t>(lowPos.y));
	GLfloat blH = GetHeightAtInteger(static_cast<size_t>(highPos.x), static_cast<size_t>(lowPos.y));

	glm::vec3 tl(highPos.x, tlH, highPos.y);
	glm::vec3 tr(lowPos.x, trH, highPos.y);
	glm::vec3 br(lowPos.x, brH, lowPos.y);
	glm::vec3 bl(highPos.x, blH, lowPos.y);

	glm::vec3 normal1 = glm::normalize(glm::cross(tr - br, bl - br));
	glm::vec3 normal2 = glm::normalize(glm::cross(bl - tl, tr - tl));

	glm::vec3 normal = (normal1 + normal2) / 2.0f;

	return normal;
}

GLfloat Terrain::GetHeightAtInteger(size_t x, size_t y) const
{
	return m_yPositions[y * m_height + x];
}

void Terrain::GenerateCell(size_t x, size_t y)
{
	size_t tl = y * m_width + x;	// top left
	size_t tr = tl + 1;				// top right
	size_t bl = tl + m_width;		// bottom left
	size_t br = bl + 1;				// bottom right

	glm::vec3 cellWorldPos(x * m_cellSize, 0, y * m_cellSize);

	glm::vec3 a = glm::vec3(0, m_yPositions[tl], 0) + cellWorldPos;
	glm::vec3 b = glm::vec3(m_cellSize, m_yPositions[tr], 0) + cellWorldPos;
	glm::vec3 c = glm::vec3(0, m_yPositions[bl], m_cellSize) + cellWorldPos;
	glm::vec3 d = glm::vec3(m_cellSize, m_yPositions[br], m_cellSize) + cellWorldPos;

	PushTriangle(a, c, d, glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1));
	PushTriangle(a, d, b, glm::vec2(0, 0), glm::vec2(1, 1), glm::vec2(1, 0));
}

void Terrain::PushTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 aTexCoord, glm::vec2 bTexCoord, glm::vec2 cTexCoord)
{
	glm::vec3 normal = glm::normalize(glm::cross(c - b, a - b));
	size_t firstIndex = m_positions.size();

	m_positions.push_back(a);
	m_positions.push_back(b);
	m_positions.push_back(c);

	m_colors.push_back(glm::vec3(1));
	m_colors.push_back(glm::vec3(1));
	m_colors.push_back(glm::vec3(1));

	m_texCoords.push_back(aTexCoord);
	m_texCoords.push_back(bTexCoord);
	m_texCoords.push_back(cTexCoord);

	m_normals.push_back(normal);
	m_normals.push_back(normal);
	m_normals.push_back(normal);

	m_indices.push_back(firstIndex);
	m_indices.push_back(firstIndex + 1);
	m_indices.push_back(firstIndex + 2);
}