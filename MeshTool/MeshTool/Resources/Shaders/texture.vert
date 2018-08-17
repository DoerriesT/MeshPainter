#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 uModelViewProjection;

void main()
{	
    gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
	vTexCoord = aTexCoord;
	vTexCoord.y = 1.0 - vTexCoord.y;
}