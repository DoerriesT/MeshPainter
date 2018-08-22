#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat3 uTransformation;

void main()
{	
	vTexCoord = aTexCoord;

    gl_Position = vec4((uTransformation * (vec3(aTexCoord, 1.0) * 2.0 - 1.0)).xy, 0.0, 1.0);
}