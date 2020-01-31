#pragma once

#include <glm/glm.hpp>

class OmniLight
{
private:
	glm::vec3 m_position;
	float m_power;
	glm::vec3 m_ambientColor;
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;

public:
	OmniLight();
	OmniLight(const glm::vec3& position);
	OmniLight(const glm::vec3& position, const glm::vec3& color, float power);
	~OmniLight();

	const glm::vec3& GetPosition() const;
	void SetPosition(const glm::vec3& position);

	float GetPower() const;
	void SetPower(const float& power);

	const glm::vec3& GetAmbientColor() const;
	void SetAmbientColor(const glm::vec3& ambientColor);

	const glm::vec3& GetDiffuseColor() const;
	void SetDiffuseColor(const glm::vec3& diffuseColor);

	const glm::vec3& GetSpecularColor() const;
	void SetSpecularColor(const glm::vec3& specularColor);
};

