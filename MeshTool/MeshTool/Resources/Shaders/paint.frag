#version 330 core

out vec4 oFragColor;

in vec3 vColor;
in vec2 vPos;

void main()
{
	float distToCenter = length(vPos) * 2.0;
	float alpha = 1.0 - distToCenter;
	oFragColor = vec4(vColor, alpha);
}