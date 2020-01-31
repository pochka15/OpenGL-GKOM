#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec3 fragPosition;
out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragLightDirection;
out vec2 fragTexCoord;

uniform mat4 transform;
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform vec3 lightPosition;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
	fragPosition = (viewTransform * modelTransform * vec4(position, 1)).xyz;
    fragColor = color;
	fragNormal = (viewTransform * modelTransform * vec4(normal, 0)).xyz;

	fragLightDirection = (viewTransform * vec4(lightPosition, 1)).xyz - fragPosition;

	fragTexCoord = texCoord;
}
