#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;
out vec3 vWorldPos;
out vec3 vNormal;

uniform mat4 uModelViewProjection;
uniform mat4 uModel;

void main()
{	
    gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
	vTexCoord = aTexCoord;
	vec4 worldPos = uModel * vec4(aPosition, 1.0);
	vWorldPos = worldPos.xyz / worldPos.w;
	vNormal = (uModel * vec4(aNormal, 0.0)).xyz;
}