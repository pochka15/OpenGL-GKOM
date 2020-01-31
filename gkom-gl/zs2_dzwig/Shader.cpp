#include "Shader.h"

#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"

Shader::Shader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile)
{
	GLuint vertexId = Compile(ReadFromFile(vertexShaderFile).c_str(), GL_VERTEX_SHADER);
	GLuint fragmentId = Compile(ReadFromFile(fragmentShaderFile).c_str(), GL_FRAGMENT_SHADER);

	// link shader program
	m_programId = glCreateProgram();
	glAttachShader(m_programId, vertexId);
	glAttachShader(m_programId, fragmentId);
	glLinkProgram(m_programId);

	// Print linking errors if any
	GLint success;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(m_programId, sizeof(infoLog), NULL, infoLog);
		std::string msg = std::string("Shader program linking: ") + infoLog;
		throw std::exception(msg.c_str());
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

Shader::~Shader()
{
}


GLuint Shader::Compile(const GLchar * shaderCode, GLenum shaderType)
{
	GLuint shader_id = glCreateShader(shaderType);
	glShaderSource(shader_id, 1, &shaderCode, NULL);
	glCompileShader(shader_id);

	// Print compile errors if any
	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader_id, sizeof(infoLog), NULL, infoLog);
		std::string msg = std::string("Shader compilation: ") + infoLog;
		throw std::exception(msg.c_str());
	}
	return shader_id;
}


GLuint Shader::GetProgramId() const
{
	return m_programId;
}

void Shader::Use() const
{
	glUseProgram(m_programId);
}

GLint Shader::GetUniformLocation(GLchar * name) const
{
	return glGetUniformLocation(m_programId, name);
}

void Shader::ApplyUniformMat4(GLchar * name, const glm::mat4 & matrix) const
{
	Use();
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ApplyUniformFloat(GLchar* name, const float& value) const
{
	Use();
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::ApplyUniformInt(GLchar* name, const GLint& value) const
{
	Use();
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::ApplyUniformVec3(GLchar* name, const glm::vec3& vector) const
{
	Use();
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
}

void Shader::ApplyTransform(glm::mat4 transform) const
{
	ApplyUniformMat4("transform", transform);
}

void Shader::ApplyTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const
{
	ApplyTransform(projection * view * model);
}

void Shader::ConfigureTransform(const Model & model, const Camera & camera) const
{
	ApplyTransform(camera.GetProjectionMatrix(), camera.ComputeViewMatrix(), model.ComputeModelMatrix());
}

std::string Shader::ReadFromFile(const GLchar * path)
{
	std::ifstream shader_file;
	shader_file.exceptions(std::ifstream::badbit);

	shader_file.open(path);
	std::stringstream shader_stream;
	shader_stream << shader_file.rdbuf();
	shader_file.close();
	return shader_stream.str();
}
