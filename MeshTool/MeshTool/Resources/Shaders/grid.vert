#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 uModelViewProjection;

void main()
{	
    gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
	vColor = aColor;
}