#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include "Camera.h"

class Model;

class Shader
{
private:
	GLuint m_programId;

	GLuint Compile(const GLchar* shaderCode, GLenum shaderType);

public:
	Shader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile);
	~Shader();

	GLuint GetProgramId() const;
	void Use() const;
	GLint GetUniformLocation(GLchar* name) const;

	void ApplyUniformMat4(GLchar* name, const glm::mat4& matrix) const;
	void ApplyUniformFloat(GLchar * name, const float & value) const;
	void ApplyUniformInt(GLchar * name, const GLint & value) const;
	void ApplyUniformVec3(GLchar * name, const glm::vec3 & vector) const;

	void ApplyTransform(glm::mat4 transform) const;
	void ApplyTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const;

protected:
	virtual void ConfigureModel(Model& model) const = 0;
	virtual void ConfigureTransform(const Model& model, const Camera& camera) const;

private:
	std::string ReadFromFile(const GLchar* path);
};