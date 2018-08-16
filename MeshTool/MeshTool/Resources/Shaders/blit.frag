#version 330 core

out vec4 oFragColor;
in vec2 vTexCoord;

layout(binding=15) uniform sampler2D uScreenTexture;

void main()
{
	vec2 texCoord = gl_FragCoord.xy / textureSize(uScreenTexture, 0);
	oFragColor = vec4(1.0, 0.0, 0.0, 1.0);//texture(uScreenTexture, texCoord).rgba;
}