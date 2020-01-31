#pragma once

#include "Shader.h"
#include "Texture.h"

class TextureShader : virtual public Shader
{
public:
	TextureShader();
	~TextureShader();

	GLint GetTextureUnitLocation() const;
	void ApplyTextureUnit(GLint textureUnit) const;

	virtual void Render(Model& model, const Camera& camera, const Texture& texture);

protected:
	virtual void ConfigureTexture(const Texture& texture) const;
	virtual void ConfigureModel(Model & model) const override;
};

