#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 pMatrix;

void main()
{
	gl_Position = pMatrix * vec4(vertexPosition, 0.0, 1.0);
	fragmentColor = vertexColor;
	fragmentUV = vec2((vertexUV.x + 1.0)/2.0, 1.0 - (vertexUV + 1.0) / 2.0);
}