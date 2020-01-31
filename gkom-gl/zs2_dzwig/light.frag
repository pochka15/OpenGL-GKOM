#version 330 core
in vec3 fragPosition;
in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragLightDirection;

out vec3 color;

uniform float lightPower;
uniform vec3 lightAmbientColor;
uniform vec3 lightDiffuseColor;
uniform vec3 lightSpecularColor;

void main()
{
	vec3 n = normalize(fragNormal);
	vec3 l = normalize(fragLightDirection);
	float cosTheta = clamp(dot(n, l), 0, 1);

	vec3 e = normalize(-fragPosition);
	vec3 r = reflect(-l, n);
	float cosAlpha = clamp(dot(e, r), 0, 1);

	float dist = length (fragLightDirection);

	vec3 ambientFinal = lightAmbientColor;
	vec3 diffuseFinal = lightDiffuseColor * lightPower * cosTheta / (dist * dist);
	vec3 specularFinal = lightSpecularColor * lightPower * pow(cosAlpha, 7) / (dist * dist);
	color = (ambientFinal + diffuseFinal + specularFinal) * fragColor;
}
