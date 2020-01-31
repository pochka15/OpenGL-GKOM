#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TextureCoords;

	Vertex()
	{
	}

	Vertex(glm::vec3 position)
		: Position(position)
	{
	}

	Vertex(glm::vec3 position, glm::vec3 color)
		: Position(position), Color(color)
	{
	}

	Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 textureCoords)
		: Position(position), Color(color), TextureCoords(textureCoords)
	{
	}
};