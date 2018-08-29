#version 330 core

layout (location = 0) in vec3 aPosition;

out vec3 vColor;
out vec2 vPos;

uniform vec3 uColor;
uniform mat4 uTransformation;

void main()
{	
    gl_Position = uTransformation * vec4(aPosition, 1.0);
	vColor = uColor;
	vPos = aPosition.xy;
}