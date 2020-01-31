#pragma once

#include <GL/glew.h>

class Texture
{
private:
	GLuint m_id;
	GLuint m_wrapping;
	GLuint m_minMagFilter;

public:
	Texture(GLchar* fileName);
	~Texture();

	GLuint GetId() const;

	GLuint GetWrapping() const;
	void SetWrapping(GLuint wrapping);
	GLuint GetMinMagFilter() const;
	void SetMinMagFilter(GLuint minMagFilter);

	void BindTo(GLuint textureUnit) const;
	void BindToDefaultUnit() const;
	void UnbindFrom(GLuint textureUnit) const;
	void UnbindFromDefaultUnit() const;
};

