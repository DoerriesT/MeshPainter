#version 330 core

const float PI = 3.14159265359;

layout(location = 0) out vec4 oFragColor;
layout(location = 1) out vec4 oUv;

uniform sampler2D uTexture;

in vec2 vTexCoord;

uniform bool uGridMode;

void main()
{
	vec4 texColor = texture(uTexture, vTexCoord);
	if (uGridMode)
	{
		oFragColor = vec4(1.0 - texColor.rgb, 1.0);
	}
	else
	{
		oFragColor = texColor;
	}
	oUv = vec4(vTexCoord, 1.0, 1.0);
}