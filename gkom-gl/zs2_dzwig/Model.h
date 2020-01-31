#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Vertex.h"
#include "LightShader.h"
#include "OmniLight.h"
#include "TextureShader.h"
#include "TextureLightShader.h"
#include "Texture.h"

class Model
{
private:
	static const GLuint BUFFER_INDEX = 0;
	static const GLuint BUFFER_POSITION = 1;
	static const GLuint BUFFER_COLOR = 2;
	static const GLuint BUFFER_TEXCOORDS = 3;
	static const GLuint BUFFER_NORMAL = 4;
	static const GLuint BUFFER_COUNT = 5;

	GLuint m_vaoId;
	GLuint m_bufferIds[BUFFER_COUNT];
	GLuint m_locations[BUFFER_COUNT];

	GLsizeiptr m_indicesCount;

	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::mat4 m_additionalTransformation;

public:
	Model();
	~Model();

	void VertexData(const Vertex* data, GLsizei count);
	void IndexData(const GLuint* data, GLsizei count);

	void PositionData(const glm::vec3* data, GLsizei count);
	void ColorData(const glm::vec3* data, GLsizei count);
	void TexCoordsData(const glm::vec2* data, GLsizei count);
	void NormalData(const glm::vec3* data, GLsizei count);

	void EnablePosition(GLuint location);
	void EnableColor(GLuint location);
	void EnableTexCoords(GLuint location);
	void EnableNormal(GLuint location);

	void DisablePosition();
	void DisableColor();
	void DisableTexCoords();
	void DisableNormal();
	void DisableAll();

	const glm::vec3& GetPosition() const;
	void SetPosition(const glm::vec3& position);

	const glm::vec3& GetScale() const;
	void SetScale(const glm::vec3& scale);

	const glm::vec3& GetRotation() const;
	void SetRotation(const glm::vec3& rotation);

	const glm::mat4& GetAdditionalTransformation() const;
	void SetAdditionalTransformation(const glm::mat4& additionalTransformation);

	glm::mat4 ComputeModelMatrix() const;

	void Bind() const;
	void Unbind() const;

	void Draw() const;

private:
	GLuint GetBufferTarget(GLuint buffer);
	template<typename T>
	void BufferData(GLuint buffer, const T* data, GLsizei count)
	{
		GLuint target = GetBufferTarget(buffer);
		glBindBuffer(target, m_bufferIds[buffer]);
		glBufferData(target, sizeof(T) * count, data, GL_STATIC_DRAW);
		glBindBuffer(target, 0);
	}

	void SetupAttribPointer(GLuint buffer, GLuint location, GLenum elementType, GLuint elementsCount)
	{
		for (GLsizei i = 0; i < BUFFER_COUNT; i++)
		{
			if (m_locations[i] == location) throw std::exception("This location is already used!");
		}
		m_locations[buffer] = location;

		Bind();
		glBindBuffer(GetBufferTarget(buffer), m_bufferIds[buffer]);
		glVertexAttribPointer(location, elementsCount, elementType, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(location);
		Unbind();
	}

	void DisableAttribPointer(GLuint buffer)
	{
		glDisableVertexAttribArray(m_locations[buffer]);
		m_locations[buffer] = -1;
	}
};

