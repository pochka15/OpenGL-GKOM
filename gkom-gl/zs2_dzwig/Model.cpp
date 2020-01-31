#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Model::Model()
	: m_indicesCount(0), m_position(0.0f), m_scale(1.0f), m_rotation(0.0f), m_additionalTransformation()
{
	for (GLsizei i = 0; i < BUFFER_COUNT; i++) m_locations[i] = -1;

	glGenBuffers(BUFFER_COUNT, (GLuint*)&m_bufferIds);

	glGenVertexArrays(1, &m_vaoId);

	Bind();
	glBindBuffer(GetBufferTarget(BUFFER_INDEX), m_bufferIds[BUFFER_INDEX]);
	Unbind();
}

Model::~Model()
{
	glDeleteVertexArrays(1, &m_vaoId);
	glDeleteBuffers(BUFFER_COUNT, (GLuint*)&m_bufferIds);
}

void Model::VertexData(const Vertex * data, GLsizei count)
{
	glm::vec3* position = new glm::vec3[count];
	glm::vec3* color = new glm::vec3[count];
	glm::vec2* texcoords = new glm::vec2[count];

	for (GLsizei i = 0; i < count; i++)
	{
		position[i] = data[i].Position;
		color[i] = data[i].Color;
		texcoords[i] = data[i].TextureCoords;
	}

	PositionData(position, count);
	ColorData(color, count);
	TexCoordsData(texcoords, count);

	delete[] position;
	delete[] color;
	delete[] texcoords;
}

void Model::IndexData(const GLuint* data, GLsizei count)
{
	BufferData(BUFFER_INDEX, data, count);

	m_indicesCount = count;
}

void Model::PositionData(const glm::vec3 * data, GLsizei count)
{
	BufferData(BUFFER_POSITION, data, count);
}

void Model::ColorData(const glm::vec3 * data, GLsizei count)
{
	BufferData(BUFFER_COLOR, data, count);
}

void Model::TexCoordsData(const glm::vec2 * data, GLsizei count)
{
	BufferData(BUFFER_TEXCOORDS, data, count);
}

void Model::NormalData(const glm::vec3 * data, GLsizei count)
{
	BufferData(BUFFER_NORMAL, data, count);
}

void Model::EnablePosition(GLuint location)
{
	SetupAttribPointer(BUFFER_POSITION, location, GL_FLOAT, 3);
}

void Model::EnableColor(GLuint location)
{
	SetupAttribPointer(BUFFER_COLOR, location, GL_FLOAT, 3);
}

void Model::EnableTexCoords(GLuint location)
{
	SetupAttribPointer(BUFFER_TEXCOORDS, location, GL_FLOAT, 2);
}

void Model::EnableNormal(GLuint location)
{
	SetupAttribPointer(BUFFER_NORMAL, location, GL_FLOAT, 3);
}

void Model::DisablePosition()
{
	DisableAttribPointer(BUFFER_POSITION);
}

void Model::DisableColor()
{
	DisableAttribPointer(BUFFER_COLOR);
}

void Model::DisableTexCoords()
{
	DisableAttribPointer(BUFFER_TEXCOORDS);
}

void Model::DisableNormal()
{
	DisableAttribPointer(BUFFER_NORMAL);
}

void Model::DisableAll()
{
	for (GLsizei i = 0; i < BUFFER_COUNT; i++)
	{
		if (m_locations[i] >= 0)
		{
			glDisableVertexAttribArray(m_locations[i]);
			m_locations[i] = -1;
		}
	}
}

const glm::vec3 & Model::GetPosition() const
{
	return m_position;
}

void Model::SetPosition(const glm::vec3 & position)
{
	m_position = position;
}

const glm::vec3 & Model::GetScale() const
{
	return m_scale;
}

void Model::SetScale(const glm::vec3 & scale)
{
	m_scale = scale;
}

const glm::vec3 & Model::GetRotation() const
{
	return m_rotation;
}

void Model::SetRotation(const glm::vec3 & rotation)
{
	m_rotation = rotation;
}

const glm::mat4 & Model::GetAdditionalTransformation() const
{
	return m_additionalTransformation;
}

void Model::SetAdditionalTransformation(const glm::mat4 & additionalTransformation)
{
	m_additionalTransformation = additionalTransformation;
}

glm::mat4 Model::ComputeModelMatrix() const
{
	return
		m_additionalTransformation *
		glm::translate(m_position) *
		glm::rotate(m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(m_scale);
}

void Model::Bind() const
{
	glBindVertexArray(m_vaoId);
}

void Model::Unbind() const
{
	glBindVertexArray(0);
}

void Model::Draw() const
{
	Bind();

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	Unbind();
}

GLuint Model::GetBufferTarget(GLuint buffer)
{
	switch (buffer)
	{
	case BUFFER_INDEX: return GL_ELEMENT_ARRAY_BUFFER;
	case BUFFER_POSITION:
	case BUFFER_COLOR:
	case BUFFER_TEXCOORDS:
	case BUFFER_NORMAL:
		return GL_ARRAY_BUFFER;
	default: throw std::exception("Invalid buffer to bind");
	}
}