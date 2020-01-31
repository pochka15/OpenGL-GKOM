#include "OmniLight.h"

OmniLight::OmniLight()
	: OmniLight(glm::vec3(0))
{
}

OmniLight::OmniLight(const glm::vec3 & position)
	: OmniLight(position, glm::vec3(1), 100)
{
}

OmniLight::OmniLight(const glm::vec3 & position, const glm::vec3 & color, float power)
	: m_position(position), m_power(power), m_ambientColor(color / 10.0f), m_diffuseColor(color), m_specularColor(1, 1, 1)
{
}

OmniLight::~OmniLight()
{
}


const glm::vec3& OmniLight::GetPosition() const
{
	return m_position;
}
void OmniLight::SetPosition(const glm::vec3& position)
{
	m_position = position;
}

float OmniLight::GetPower() const
{
	return m_power;
}
void OmniLight::SetPower(const float& power)
{
	m_power = power;
}

const glm::vec3& OmniLight::GetAmbientColor() const
{
	return m_ambientColor;
}
void OmniLight::SetAmbientColor(const glm::vec3& ambientColor)
{
	m_ambientColor = ambientColor;
}

const glm::vec3& OmniLight::GetDiffuseColor() const
{
	return m_diffuseColor;
}
void OmniLight::SetDiffuseColor(const glm::vec3& diffuseColor)
{
	m_diffuseColor = diffuseColor;
}

const glm::vec3& OmniLight::GetSpecularColor() const
{
	return m_specularColor;
}
void OmniLight::SetSpecularColor(const glm::vec3& specularColor)
{
	m_specularColor = specularColor;
}