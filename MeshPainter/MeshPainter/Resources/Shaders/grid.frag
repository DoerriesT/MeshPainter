#version 330 core

const float PI = 3.14159265359;

layout(location = 0) out vec4 oFragColor;

in vec3 vColor;

void main()
{
	oFragColor = vec4(vColor, 1.0);
}