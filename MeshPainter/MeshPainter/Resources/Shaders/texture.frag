#version 330 core

const float PI = 3.14159265359;

layout(location = 0) out vec4 oFragColor;
layout(location = 1) out vec4 oUv;

uniform sampler2D uTexture;

in vec2 vTexCoord;

void main()
{
	oFragColor = texture(uTexture, vTexCoord).rgba;
	oUv = vec4(vTexCoord, 1.0, 1.0);
}