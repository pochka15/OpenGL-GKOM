#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader();
	~BasicShader();

	void Render(Model & model, const Camera & camera) const;

protected:
	virtual void ConfigureModel(Model & model) const override;
};

