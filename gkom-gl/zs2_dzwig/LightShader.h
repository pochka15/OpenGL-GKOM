#pragma once

#include "Shader.h"
#include "OmniLight.h"

class LightShader : virtual public Shader
{
public:
	LightShader();
	~LightShader();

	GLint GetLightPositionLocation() const;
	GLint GetLightPowerLocation() const;
	GLint GetLightAmbientColorLocation() const;
	GLint GetLightDiffuseColorLocation() const;
	GLint GetLightSpecularColorLocation() const;
	GLint GetModelTransformLocation() const;
	GLint GetViewTransformLocation() const;

	void ApplyLight(const OmniLight& light, const glm::mat4& modelTransform, const glm::mat4& viewTransform) const;

	virtual void Render(Model& model, const Camera& camera, const OmniLight& light) const;

protected:
	virtual void ConfigureLight(const Model& model, const Camera& camera, const OmniLight& light) const;
	virtual void ConfigureModel(Model & model) const override;
};

