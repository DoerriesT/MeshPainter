#version 330 core

const float PI = 3.14159265359;

layout(location = 0) out vec4 oFragColor;

in vec2 vTexCoord;

void main()
{
	oFragColor = vec4(vTexCoord, 0.0, 1.0);
}