#include "TextureShader.h"

#include "Model.h"

TextureShader::TextureShader()
	: Shader("texture.vert", "texture.frag")
{
}


TextureShader::~TextureShader()
{
}

GLint TextureShader::GetTextureUnitLocation() const
{
	return Shader::GetUniformLocation("Texture");
}

void TextureShader::ApplyTextureUnit(GLint textureUnit) const
{
	Use();
	glUniform1i(GetTextureUnitLocation(), textureUnit);
}

void TextureShader::Render(Model & model, const Camera & camera, const Texture & texture)
{
	ConfigureTexture(texture);
	ConfigureModel(model);
	ConfigureTransform(model, camera);

	model.Draw();
}

void TextureShader::ConfigureTexture(const Texture & texture) const
{
	texture.BindToDefaultUnit();
	ApplyTextureUnit(0);
}

void TextureShader::ConfigureModel(Model & model) const
{
	model.DisableAll();
	model.EnablePosition(0);
	model.EnableColor(1);
	model.EnableTexCoords(2);
}
