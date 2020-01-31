#include "TextureLightShader.h"

#include <glm/gtc/type_ptr.hpp>
#include "Model.h"

TextureLightShader::TextureLightShader()
	: Shader("texture_light.vert", "texture_light.frag"), LightShader(), TextureShader()
{
}

TextureLightShader::~TextureLightShader()
{
}

void TextureLightShader::ConfigureModel(Model & model) const
{
	model.DisableAll();
	model.EnablePosition(0);
	model.EnableColor(1);
	model.EnableNormal(2);
	model.EnableTexCoords(3);
}

void TextureLightShader::Render(Model & model, const Camera & camera, const Texture & texture, const OmniLight & light) const
{
	ConfigureLight(model, camera, light);
	ConfigureTexture(texture);
	ConfigureModel(model);
	ConfigureTransform(model, camera);

	model.Draw();
}
