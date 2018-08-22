#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;

void main()
{	
	vTexCoord = aTexCoord;

    gl_Position = vec4(aTexCoord * 2.0 - 1.0, 0.0, 1.0);
}