#version 330 core

out vec4 oFragColor;
in vec2 vTexCoord;

layout(binding=15) uniform sampler2D uSourceTexture;

void main()
{
	oFragColor = texture(uSourceTexture, vTexCoord).rgba;
}