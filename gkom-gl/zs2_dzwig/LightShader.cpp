#include "LightShader.h"

#include <glm/gtc/type_ptr.hpp>
#include "Model.h"

LightShader::LightShader()
	: Shader("light.vert", "light.frag")
{
}

LightShader::~LightShader()
{
}

GLint LightShader::GetLightPositionLocation() const
{
	return Shader::GetUniformLocation("lightPosition");
}

GLint LightShader::GetLightPowerLocation() const
{
	return Shader::GetUniformLocation("lightPower");
}

GLint LightShader::GetLightAmbientColorLocation() const
{
	return Shader::GetUniformLocation("lightAmbientColor");
}

GLint LightShader::GetLightDiffuseColorLocation() const
{
	return Shader::GetUniformLocation("lightDiffuseColor");
}

GLint LightShader::GetLightSpecularColorLocation() const
{
	return Shader::GetUniformLocation("lightSpecularColor");
}

GLint LightShader::GetModelTransformLocation() const
{
	return GetUniformLocation("modelTransform");
}

GLint LightShader::GetViewTransformLocation() const
{
	return GetUniformLocation("viewTransform");
}

void LightShader::ApplyLight(const OmniLight & light, const glm::mat4& modelTransform, const glm::mat4& viewTransform) const
{
	Use();
	glUniform3fv(GetLightPositionLocation(), 1, glm::value_ptr(light.GetPosition()));
	glUniform1f(GetLightPowerLocation(), light.GetPower());
	glUniform3fv(GetLightAmbientColorLocation(), 1, glm::value_ptr(light.GetAmbientColor()));
	glUniform3fv(GetLightDiffuseColorLocation(), 1, glm::value_ptr(light.GetDiffuseColor()));
	glUniform3fv(GetLightSpecularColorLocation(), 1, glm::value_ptr(light.GetSpecularColor()));
	glUniformMatrix4fv(GetModelTransformLocation(), 1, GL_FALSE, glm::value_ptr(modelTransform));
	glUniformMatrix4fv(GetViewTransformLocation(), 1, GL_FALSE, glm::value_ptr(viewTransform));
}

void LightShader::ConfigureLight(const Model& model, const Camera& camera, const OmniLight & light) const
{
	ApplyLight(light, model.ComputeModelMatrix(), camera.ComputeViewMatrix());
}

void LightShader::ConfigureModel(Model & model) const
{
	model.DisableAll();
	model.EnablePosition(0);
	model.EnableColor(1);
	model.EnableNormal(2);
}

void LightShader::Render(Model & model, const Camera & camera, const OmniLight & light) const
{
	ConfigureLight(model, camera, light);
	ConfigureModel(model);
	ConfigureTransform(model, camera);

	model.Draw();
}
