#pragma once

#include "Vertex.h"
#include "Model.h"

class ModelGenerator
{
private:
	ModelGenerator();
	~ModelGenerator();

public:
	static void Cuboid(Model& model, glm::vec3 size, glm::vec3 color);
	static void TexturedCuboid(Model& model, glm::vec3 size);
	static void Trapezioid(Model& model, float p1, float p2, glm::vec3 size, glm::vec3 color);

	static void Plane(Model& model, glm::vec3 size, glm::vec3 color);
	static void TexturedPlane(Model & model, glm::vec3 size);
	static void TexturedPlane(Model & model, glm::vec3 size, glm::vec2 texCoordTopLeft, glm::vec2 texCoordBottomRight);
	static void Triangle(Model& model, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color);
	static void TexturedTriangle(Model& model, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 aTexCoord, glm::vec2 bTexCoord, glm::vec2 cTexCoord);

	static void ChassisTrack(Model& model, glm::vec3 size, glm::vec3 color, GLuint wheelPrecision = 20);
	static void Cylinder(Model& model, GLfloat height, GLfloat radius, glm::vec3 color, GLuint precision = 20);
};

