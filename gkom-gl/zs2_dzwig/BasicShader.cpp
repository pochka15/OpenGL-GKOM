#include "BasicShader.h"

#include "Model.h"

BasicShader::BasicShader()
	: Shader("basic.vert", "basic.frag")
{
}


BasicShader::~BasicShader()
{
}

void BasicShader::Render(Model & model, const Camera & camera) const
{
	ConfigureModel(model);
	ConfigureTransform(model, camera);

	model.Draw();
}

void BasicShader::ConfigureModel(Model & model) const
{
	model.DisableAll();
	model.EnablePosition(0);
	model.EnableColor(1);
}
