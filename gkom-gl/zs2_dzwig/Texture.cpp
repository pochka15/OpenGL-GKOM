#include "Texture.h"

#include <exception>
#include <SOIL.h>


Texture::Texture(GLchar* fileName)
	: m_wrapping(GL_REPEAT), m_minMagFilter(GL_LINEAR)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Failed to load texture file");

	glGenTextures(1, &m_id);

	BindToDefaultUnit();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	UnbindFromDefaultUnit();
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

GLuint Texture::GetId() const
{
	return m_id;
}

GLuint Texture::GetWrapping() const
{
	return m_wrapping;
}

void Texture::SetWrapping(GLuint wrapping)
{
	m_wrapping = wrapping;
}

GLuint Texture::GetMinMagFilter() const
{
	return m_minMagFilter;
}

void Texture::SetMinMagFilter(GLuint minMagFilter)
{
	m_minMagFilter = minMagFilter;
}

void Texture::BindTo(GLuint textureUnit) const
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_id);

	// apply texture parameters to choosen texture unit
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_minMagFilter);
}

void Texture::BindToDefaultUnit() const
{
	BindTo(GL_TEXTURE0);
}

void Texture::UnbindFrom(GLuint textureUnit) const
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UnbindFromDefaultUnit() const
{
	UnbindFrom(GL_TEXTURE0);
}
