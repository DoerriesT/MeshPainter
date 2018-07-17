#version 330 core

const float PI = 3.14159265359;

layout(location = 0) out vec4 oFragColor;

in vec2 vTexCoord;
in vec3 vWorldPos;
in vec3 vNormal;

const vec3 LIGHT_DIR = normalize(vec3(1.0, 1.0, 1.0));

uniform vec3 uCamPos;
uniform bool uLineMode;

void main()
{
	if (uLineMode)
	{
		oFragColor = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else
	{
		vec3 diffuse = vec3(1.0);
		vec3 L = LIGHT_DIR;
		vec3 V = normalize(uCamPos - vWorldPos);
		vec3 H = normalize(V + L);
		vec3 N = normalize(vNormal);
		float NdotL = clamp(dot(N, L), 0.0, 1.0);
		float NdotH = clamp(dot(N, H), 0.0, 1.0);
		float specular = pow(NdotH, 128.0);
		vec3 color =  vec3(0.1) + NdotL * diffuse + specular * vec3(1.0);
		oFragColor = vec4(color, 1.0);
	}
}