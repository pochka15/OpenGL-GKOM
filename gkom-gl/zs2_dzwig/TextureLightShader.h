#pragma once

#include "Shader.h"
#include "TextureShader.h"
#include "LightShader.h"
#include "OmniLight.h"
#include "Texture.h"
#include "Camera.h"

class TextureLightShader : public TextureShader, public LightShader
{
public:
	TextureLightShader();
	~TextureLightShader();

	virtual void Render(Model& model, const Camera& camera, const Texture& texture, const OmniLight& light) const;

protected:
	virtual void ConfigureModel(Model & model) const override;
};

