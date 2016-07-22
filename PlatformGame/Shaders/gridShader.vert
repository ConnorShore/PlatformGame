#version 330 core

layout(location = 0) in vec2 vertexPosition;

out vec2 fragmentPosition;

uniform mat4 pMatrix;

void main()
{
	gl_Position = pMatrix * vec4(vertexPosition, 0.0, 1.0);
	fragmentPosition = vertexPosition;
}