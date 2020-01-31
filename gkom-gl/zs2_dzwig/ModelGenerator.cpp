#include "ModelGenerator.h"

#include <glm/gtc/constants.hpp>
#include <iostream>
#include <vector>

ModelGenerator::ModelGenerator()
{
}


ModelGenerator::~ModelGenerator()
{
}

void ModelGenerator::Cuboid(Model& model, glm::vec3 size, glm::vec3 color)
{
	glm::vec3 halfSize = size / 2.0f;

	glm::vec3 tlf = glm::vec3(-halfSize.x, halfSize.y, halfSize.z); // top left front
	glm::vec3 trf = glm::vec3(halfSize.x, halfSize.y, halfSize.z); // top right front
	glm::vec3 brf = glm::vec3(halfSize.x, -halfSize.y, halfSize.z); // bottom right front
	glm::vec3 blf = glm::vec3(-halfSize.x, -halfSize.y, halfSize.z); // bottom left front
	glm::vec3 tlb = glm::vec3(-halfSize.x, halfSize.y, -halfSize.z); // top left back
	glm::vec3 trb = glm::vec3(halfSize.x, halfSize.y, -halfSize.z); // top right back
	glm::vec3 brb = glm::vec3(halfSize.x, -halfSize.y, -halfSize.z); // bottom right back
	glm::vec3 blb = glm::vec3(-halfSize.x, -halfSize.y, -halfSize.z);  // bottom left back

	glm::vec3 positions[] = {
		trf, tlf, blf, brf, // front
		trb, tlb, blb, brb, // back
		tlf, tlb, blb, blf, // left
		trb, trf, brf, brb, // right
		trb, tlb, tlf, trf, // top
		brf, blf, blb, brb  // bottom
	};

	glm::vec3 colors[24];
	for (GLsizei i = 0; i < _countof(colors); i++) colors[i] = color;

	glm::vec3 px = glm::vec3(1, 0, 0); // plus X normal
	glm::vec3 mx = glm::vec3(-1, 0, 0); // minus X normal
	glm::vec3 py = glm::vec3(0, 1, 0); // plus Y normal
	glm::vec3 my = glm::vec3(0, -1, 0); // minus Y normal
	glm::vec3 pz = glm::vec3(0, 0, 1); // plus Z normal
	glm::vec3 mz = glm::vec3(0, 0, -1); // minus Z normal

	glm::vec3 normals[] = {
		pz, pz, pz, pz, // front
		mz, mz, mz, mz, // back
		mx, mx, mx, mx, // left
		px, px, px, px, // right
		py, py, py, py, // top
		my, my, my, my  // bottom
	};

	GLuint indices[] = {
		0, 1, 2, 0, 2, 3, // front
		4, 5, 6, 4, 6, 7, // back
		8, 9, 10, 8, 10, 11, // left
		12, 13, 14, 12, 14, 15, // right
		16, 17, 18, 16, 18, 19, // top
		20, 21, 22, 20, 22, 23 // bottom
	};

	model.PositionData(positions, _countof(positions));
	model.ColorData(colors, _countof(colors));
	model.NormalData(normals, _countof(normals));
	model.IndexData(indices, _countof(indices));
}

void ModelGenerator::Trapezioid(Model& model, float p1, float p2, glm::vec3 size, glm::vec3 color)
{
	glm::vec3 halfSize = size / 2.0f;

	glm::vec3 tlf = glm::vec3(-halfSize.x * p1, halfSize.y, halfSize.z); // top left front
	glm::vec3 trf = glm::vec3(halfSize.x * p2, halfSize.y, halfSize.z); // top right front
	glm::vec3 brf = glm::vec3(halfSize.x, -halfSize.y, halfSize.z); // bottom right front
	glm::vec3 blf = glm::vec3(-halfSize.x, -halfSize.y, halfSize.z); // bottom left front
	glm::vec3 tlb = glm::vec3(-halfSize.x * p1, halfSize.y, -halfSize.z); // top left back
	glm::vec3 trb = glm::vec3(halfSize.x * p2, halfSize.y, -halfSize.z); // top right back
	glm::vec3 brb = glm::vec3(halfSize.x, -halfSize.y, -halfSize.z); // bottom right back
	glm::vec3 blb = glm::vec3(-halfSize.x, -halfSize.y, -halfSize.z);  // bottom left back

	glm::vec3 positions[] = {
		trf, tlf, blf, brf, // front
		trb, tlb, blb, brb, // back
		tlf, tlb, blb, blf, // left
		trb, trf, brf, brb, // right
		trb, tlb, tlf, trf, // top
		brf, blf, blb, brb  // bottom
	};

	glm::vec3 colors[24];
	for (GLsizei i = 0; i < _countof(colors); i++) colors[i] = color;

	// TODO: normals.

	float tanA = (1.0f - p2) * halfSize.x / 2.0f * halfSize.y;
	float a = atanf(tanA);

	float tanB = (1.0f - p1) * halfSize.x / 2.0f * halfSize.y;
	float b = atanf(tanB);


	glm::vec3 px = glm::vec3(cosf(a), sin(a), 0); // plus X normal
	glm::vec3 mx = glm::vec3(-cosf(b), sin(b), 0); // minus X normal
	glm::vec3 py = glm::vec3(0, 1, 0); // plus Y normal
	glm::vec3 my = glm::vec3(0, -1, 0); // minus Y normal
	glm::vec3 pz = glm::vec3(0, 0, 1); // plus Z normal
	glm::vec3 mz = glm::vec3(0, 0, -1); // minus Z normal

	glm::vec3 normals[] = {
		pz, pz, pz, pz, // front
		mz, mz, mz, mz, // back
		mx, mx, mx, mx, // left
		px, px, px, px, // right
		py, py, py, py, // top
		my, my, my, my  // bottom
	};

	GLuint indices[] = {
		0, 1, 2, 0, 2, 3, // front
		4, 5, 6, 4, 6, 7, // back
		8, 9, 10, 8, 10, 11, // left
		12, 13, 14, 12, 14, 15, // right
		16, 17, 18, 16, 18, 19, // top
		20, 21, 22, 20, 22, 23 // bottom
	};

	model.PositionData(positions, _countof(positions));
	model.ColorData(colors, _countof(colors));
	model.NormalData(normals, _countof(normals));
	model.IndexData(indices, _countof(indices));
}

void ModelGenerator::TexturedCuboid(Model& model, glm::vec3 size) {
	// todo: color

	glm::vec3 halfSize = size / 2.0f;

	const GLuint TLF = 0; // TopLeftFront
	const GLuint TRF = 1; // TopRightFront
	const GLuint BRF = 2; // BottomRightFront
	const GLuint BLF = 3; // BottomLeftFront
	const GLuint TLB = 4; // TopLeftBack
	const GLuint TRB = 5; // TopRightBack
	const GLuint BRB = 6; // BottomRightBack
	const GLuint BLB = 7; // BottomLeftBack


	glm::vec3 positions[] = {
		glm::vec3(-halfSize.x, halfSize.y, halfSize.z), // top left front
		glm::vec3(halfSize.x, halfSize.y, halfSize.z), // top right front
		glm::vec3(halfSize.x, -halfSize.y, halfSize.z), // bottom right front
		glm::vec3(-halfSize.x, -halfSize.y, halfSize.z), // bottom left front
		glm::vec3(-halfSize.x, halfSize.y, -halfSize.z), // top left back
		glm::vec3(halfSize.x, halfSize.y, -halfSize.z), // top right back
		glm::vec3(halfSize.x, -halfSize.y, -halfSize.z), // bottom right back
		glm::vec3(-halfSize.x, -halfSize.y, -halfSize.z)  // bottom left back
	};

	Vertex vertices[] = {
		// coordinates			// color			// texture

		// front
		Vertex(positions[TRF], glm::vec3(1.0f),	glm::vec2(1.0f,  0.0f)),	// 0
		Vertex(positions[TLF], glm::vec3(1.0f),	glm::vec2(0.0f,  0.0f)),	// 1
		Vertex(positions[BLF], glm::vec3(1.0f),	glm::vec2(0.0f,  1.0f)),	// 2
		Vertex(positions[BRF], glm::vec3(1.0f),	glm::vec2(1.0f,  1.0f)),	// 3

				// back
		Vertex(positions[TRB], glm::vec3(1.0f),	glm::vec2(0.0f,  0.0f)),	// 4
		Vertex(positions[TLB], glm::vec3(1.0f),	glm::vec2(1.0f,  0.0f)),	// 5
		Vertex(positions[BLB], glm::vec3(1.0f),	glm::vec2(1.0f,  1.0f)),	// 6
		Vertex(positions[BRB], glm::vec3(1.0f),	glm::vec2(0.0f,  1.0f)),	// 7

				// left
		Vertex(positions[TLF], glm::vec3(1.0f),	glm::vec2(1.0f,  0.0f)),
		Vertex(positions[TLB], glm::vec3(1.0f),	glm::vec2(0.0f,  0.0f)),
		Vertex(positions[BLB], glm::vec3(1.0f),	glm::vec2(0.0f,  1.0f)),
		Vertex(positions[BLF], glm::vec3(1.0f),	glm::vec2(1.0f,  1.0f)),

		// right
		Vertex(positions[TRB], glm::vec3(1.0f),	glm::vec2(1.0f,  0.0f)),
		Vertex(positions[TRF], glm::vec3(1.0f),	glm::vec2(0.0f,  0.0f)),
		Vertex(positions[BRF], glm::vec3(1.0f),	glm::vec2(0.0f,  1.0f)),
		Vertex(positions[BRB], glm::vec3(1.0f),	glm::vec2(1.0f,  1.0f)),

		// top
		Vertex(positions[TRB], glm::vec3(1.0f),	glm::vec2(1.0f,  0.0f)),
		Vertex(positions[TLB], glm::vec3(1.0f),	glm::vec2(0.0f,  0.0f)),
		Vertex(positions[TLF], glm::vec3(1.0f),	glm::vec2(0.0f,  1.0f)),
		Vertex(positions[TRF], glm::vec3(1.0f),	glm::vec2(1.0f,  1.0f)),

		// bottom
		Vertex(positions[BRF], glm::vec3(1.0f),	glm::vec2(1.0f,  0.0f)),
		Vertex(positions[BLF], glm::vec3(1.0f),	glm::vec2(0.0f,  0.0f)),
		Vertex(positions[BLB], glm::vec3(1.0f),	glm::vec2(0.0f,  1.0f)),
		Vertex(positions[BRB], glm::vec3(1.0f),	glm::vec2(1.0f,  1.0f)),
	};

	GLuint indices[] = {
		0, 1, 2, 0, 2, 3, // front
		4, 5, 6, 4, 6, 7, // back
		8, 9, 10, 8, 10, 11, // left
		12, 13, 14, 12, 14, 15, // right
		16, 17, 18, 16, 18, 19, // top
		20, 21, 22, 20, 22, 23 // bottom
	};

	model.VertexData(vertices, _countof(vertices));
	model.IndexData(indices, _countof(indices));
}

void ModelGenerator::Plane(Model & model, glm::vec3 size, glm::vec3 color)
{
	glm::vec3 halfSize = size / 2.0f;

	const GLuint TL = 0; // TopLeft
	const GLuint TR = 1; // TopRight
	const GLuint BR = 2; // BottomRight
	const GLuint BL = 3; // BottomLeft

	glm::vec3 positions[] = {
		glm::vec3(-halfSize.x, 0, -halfSize.z), // top left
		glm::vec3(halfSize.x, 0, -halfSize.z), // top right
		glm::vec3(halfSize.x, 0, halfSize.z), // bottom right
		glm::vec3(-halfSize.x, 0, halfSize.z), // bottom left
	};

	glm::vec3 colors[] = {
		color,
		color,
		color,
		color
	};

	GLuint indices[] = {
		0, 1, 3, 1, 2, 3
	};

	model.PositionData(positions, _countof(positions));
	model.ColorData(colors, _countof(colors));
	model.IndexData(indices, _countof(indices));
}
void ModelGenerator::TexturedPlane(Model & model, glm::vec3 size)
{
	TexturedPlane(model, size, glm::vec2(0), glm::vec2(1));
}
void ModelGenerator::TexturedPlane(Model & model, glm::vec3 size, glm::vec2 texCoordTopLeft, glm::vec2 texCoordBottomRight)
{
	glm::vec3 halfSize = size / 2.0f;

	const GLuint TL = 0; // TopLeft
	const GLuint TR = 1; // TopRight
	const GLuint BR = 2; // BottomRight
	const GLuint BL = 3; // BottomLeft

	glm::vec3 positions[] = {
		glm::vec3(-halfSize.x, 0, -halfSize.z), // top left
		glm::vec3(halfSize.x, 0, -halfSize.z), // top right
		glm::vec3(halfSize.x, 0, halfSize.z), // bottom right
		glm::vec3(-halfSize.x, 0, halfSize.z), // bottom left
	};

	glm::vec3 colors[] = {
		glm::vec3(1),
		glm::vec3(1),
		glm::vec3(1),
		glm::vec3(1)
	};

	glm::vec2 texcoords[] = {
		texCoordTopLeft,
		glm::vec2(texCoordBottomRight.x, texCoordTopLeft.y),
		texCoordBottomRight,
		glm::vec2(texCoordTopLeft.y, texCoordBottomRight.x)
	};

	GLuint indices[] = {
		0, 1, 3, 1, 2, 3
	};

	model.PositionData(positions, _countof(positions));
	model.ColorData(colors, _countof(colors));
	model.TexCoordsData(texcoords, _countof(texcoords));
	model.IndexData(indices, _countof(indices));
}

void ModelGenerator::Triangle(Model & model, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color)
{
	glm::vec3 normal = glm::normalize(glm::cross(c - b, a - b));

	glm::vec3 positions[] = {
		a,
		b,
		c
	};

	glm::vec3 colors[] = {
		color,
		color,
		color
	};

	glm::vec3 normals[] = {
		normal,
		normal,
		normal
	};

	GLuint indices[] = {
		0, 1, 2
	};

	model.PositionData(positions, _countof(positions));
	model.ColorData(colors, _countof(colors));
	model.NormalData(normals, _countof(normals));
	model.IndexData(indices, _countof(indices));
}

void ModelGenerator::TexturedTriangle(Model & model, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 aTexCoord, glm::vec2 bTexCoord, glm::vec2 cTexCoord)
{
	glm::vec3 normal = glm::normalize(glm::cross(c - b, a - b));

	glm::vec3 positions[] = {
		a,
		b,
		c
	};

	glm::vec3 colors[] = {
		glm::vec3(1),
		glm::vec3(1),
		glm::vec3(1)
	};

	glm::vec2 texCoords[] = {
		aTexCoord,
		bTexCoord,
		cTexCoord
	};

	glm::vec3 normals[] = {
		normal,
		normal,
		normal
	};

	GLuint indices[] = {
		0, 1, 2
	};

	model.PositionData(positions, _countof(positions));
	model.ColorData(colors, _countof(colors));
	model.TexCoordsData(texCoords, _countof(texCoords));
	model.NormalData(normals, _countof(normals));
	model.IndexData(indices, _countof(indices));
}

void ModelGenerator::ChassisTrack(Model& model, glm::vec3 size, glm::vec3 color, GLuint wheelPrecision)
{
	GLfloat wheelRadius = size.y / 2;
	GLfloat trackHeight = size.y;
	GLfloat wheelStep = glm::pi<GLfloat>() / (wheelPrecision + 1);

	std::vector<glm::vec2> points;
	points.push_back(glm::vec2(wheelRadius, trackHeight));
	points.push_back(glm::vec2(size.z - wheelRadius, trackHeight));

	// wheel
	GLfloat baseAngle = glm::pi<GLfloat>() / 2;
	glm::vec2 wheelCenter(size.z - wheelRadius, wheelRadius);
	for (GLuint i = 1; i <= wheelPrecision; i++)
	{
		GLfloat angle = baseAngle - i * wheelStep;
		points.push_back(glm::vec2(wheelRadius * glm::cos(angle), wheelRadius * glm::sin(angle)) + wheelCenter);
	}

	points.push_back(glm::vec2(size.z - wheelRadius, 0));
	points.push_back(glm::vec2(wheelRadius, 0));

	// wheel
	baseAngle = 3 * glm::pi<GLfloat>() / 2;
	wheelCenter = glm::vec2(wheelRadius, wheelRadius);
	for (GLuint i = 1; i <= wheelPrecision; i++)
	{
		GLfloat angle = baseAngle - i * wheelStep;
		points.push_back(glm::vec2(wheelRadius * glm::cos(angle), wheelRadius * glm::sin(angle)) + wheelCenter);
	}

	std::vector<glm::vec3> positions;
	GLfloat trackHalfWidth = size.x / 2;
	GLfloat trackHalfLength = size.z / 2;
	for (auto i = points.begin(); i != points.end(); i++)
	{
		positions.push_back(glm::vec3(-trackHalfWidth, i->y, i->x - trackHalfLength));
		positions.push_back(glm::vec3(trackHalfWidth, i->y, i->x - trackHalfLength));
	}

	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec3> vertexNormals;
	std::vector<glm::vec3> vertexColors;
	std::vector<GLuint> vertexIndices;

	assert(positions.size() % 2 == 0);
	GLint pSize = positions.size();
	for (GLint i = 0; i < pSize; i += 2)
	{
		GLint v0 = i;
		GLint v1 = i + 1;
		GLint v2 = (i + 2) % pSize;
		GLint v3 = (i + 3) % pSize;
		GLuint currentIndex = vertexPositions.size();

		vertexPositions.push_back(positions[v0]);
		vertexPositions.push_back(positions[v1]);
		vertexPositions.push_back(positions[v2]);
		vertexPositions.push_back(positions[v3]);

		vertexColors.push_back(color);
		vertexColors.push_back(color);
		vertexColors.push_back(color);
		vertexColors.push_back(color);

		vertexIndices.push_back(currentIndex + 0);
		vertexIndices.push_back(currentIndex + 1);
		vertexIndices.push_back(currentIndex + 2);
		vertexIndices.push_back(currentIndex + 1);
		vertexIndices.push_back(currentIndex + 3);
		vertexIndices.push_back(currentIndex + 2);

		glm::vec3 normal = glm::normalize(glm::cross(positions[v0] - positions[v1], positions[v3] - positions[v1]));
		vertexNormals.push_back(normal);
		vertexNormals.push_back(normal);
		vertexNormals.push_back(normal);
		vertexNormals.push_back(normal);
	}

	GLuint leftFirstIndex, leftPrevIndex;
	GLuint rightFirstIndex, rightPrevIndex;
	glm::vec3 leftNormal = glm::vec3(-1, 0, 0);
	glm::vec3 rightNormal = glm::vec3(1, 0, 0);
	for (GLint i = 0; i < pSize; i += 2)
	{
		GLuint currentIndex = vertexPositions.size();
		vertexPositions.push_back(positions[i]);
		vertexColors.push_back(color);
		vertexNormals.push_back(leftNormal);
		if (i == 0) leftFirstIndex = currentIndex;
		if (i >= 4)
		{
			vertexIndices.push_back(leftFirstIndex);
			vertexIndices.push_back(leftPrevIndex);
			vertexIndices.push_back(currentIndex);
		}
		leftPrevIndex = currentIndex;

		currentIndex = vertexPositions.size();
		vertexPositions.push_back(positions[i + 1]);
		vertexColors.push_back(color);
		vertexNormals.push_back(rightNormal);
		if (i == 0) rightFirstIndex = currentIndex;
		if (i >= 4)
		{
			vertexIndices.push_back(rightFirstIndex);
			vertexIndices.push_back(rightPrevIndex);
			vertexIndices.push_back(currentIndex);
		}
		rightPrevIndex = currentIndex;
	}

	assert(vertexPositions.size() == vertexNormals.size() && vertexNormals.size() == vertexColors.size());
	model.PositionData(&vertexPositions.front(), vertexPositions.size());
	model.ColorData(&vertexColors.front(), vertexColors.size());
	model.NormalData(&vertexNormals.front(), vertexNormals.size());
	model.IndexData(&vertexIndices.front(), vertexIndices.size());
}

void ModelGenerator::Cylinder(Model & model, GLfloat height, GLfloat radius, glm::vec3 color, GLuint precision)
{
	GLfloat halfHeight = height / 2;

	std::vector<glm::vec2> points;
	GLfloat step = (2 * glm::pi<GLfloat>()) / precision;
	for (GLuint i = 0; i < precision; i++)
	{
		GLfloat angle = i * step;
		points.push_back(glm::vec2(radius * glm::cos(angle), radius * glm::sin(angle)));
	}

	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec3> vertexColors;
	std::vector<glm::vec3> vertexNormals;
	std::vector<GLuint> vertexIndices;

	GLuint pSize = points.size();
	glm::vec3 upNormal = glm::vec3(0, 1, 0);
	glm::vec3 downNormal = glm::vec3(0, -1, 0);
	GLuint topFirstIndex, topPrevIndex;
	GLuint downFirstIndex, downPrevIndex;
	for (GLuint i = 0; i < pSize; i++)
	{
		GLuint currentIndex = vertexPositions.size();
		vertexPositions.push_back(glm::vec3(points[i].x, halfHeight, points[i].y));
		vertexColors.push_back(color);
		vertexNormals.push_back(upNormal);
		if (i == 0) topFirstIndex = currentIndex;
		if (i >= 2)
		{
			vertexIndices.push_back(topFirstIndex);
			vertexIndices.push_back(topPrevIndex);
			vertexIndices.push_back(currentIndex);
		}
		topPrevIndex = currentIndex;
		
		currentIndex = vertexPositions.size();
		vertexPositions.push_back(glm::vec3(points[i].x, -halfHeight, points[i].y));
		vertexColors.push_back(color);
		vertexNormals.push_back(downNormal);
		if (i == 0) downFirstIndex = currentIndex;
		if (i >= 2)
		{
			vertexIndices.push_back(downFirstIndex);
			vertexIndices.push_back(downPrevIndex);
			vertexIndices.push_back(currentIndex);
		}
		downPrevIndex = currentIndex;

		GLint p0 = i;
		GLint p1 = (i + 1) % pSize;
		currentIndex = vertexPositions.size();
		glm::vec3 v0 = glm::vec3(points[p0].x, -halfHeight, points[p0].y);
		glm::vec3 v1 = glm::vec3(points[p1].x, -halfHeight, points[p1].y);
		glm::vec3 v2 = glm::vec3(points[p1].x, halfHeight, points[p1].y);
		glm::vec3 v3 = glm::vec3(points[p0].x, halfHeight, points[p0].y);
		glm::vec3 normal = glm::normalize(glm::cross(v0 - v1, v2 - v1));
		vertexPositions.push_back(v0);
		vertexPositions.push_back(v1);
		vertexPositions.push_back(v2);
		vertexPositions.push_back(v3);

		vertexColors.push_back(color);
		vertexColors.push_back(color);
		vertexColors.push_back(color);
		vertexColors.push_back(color);

		vertexNormals.push_back(normal);
		vertexNormals.push_back(normal);
		vertexNormals.push_back(normal);
		vertexNormals.push_back(normal);

		vertexIndices.push_back(currentIndex);
		vertexIndices.push_back(currentIndex + 1);
		vertexIndices.push_back(currentIndex + 2);
		vertexIndices.push_back(currentIndex + 2);
		vertexIndices.push_back(currentIndex + 3);
		vertexIndices.push_back(currentIndex);
	}

	assert(vertexPositions.size() == vertexNormals.size() && vertexNormals.size() == vertexColors.size());
	model.PositionData(&vertexPositions.front(), vertexPositions.size());
	model.ColorData(&vertexColors.front(), vertexColors.size());
	model.NormalData(&vertexNormals.front(), vertexNormals.size());
	model.IndexData(&vertexIndices.front(), vertexIndices.size());
}
