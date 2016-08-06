#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;
out vec2 toLightVector[4];

uniform mat4 pMatrix;
uniform vec2 lightPosition[4];

void main()
{
	vec4 worldPos = pMatrix * vec4(vertexPosition, 0.0, 1.0);
	gl_Position = worldPos;
	fragmentColor = vertexColor;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
	
	for(int i = 0; i < 4; i++) {
		toLightVector[i] = lightPosition[i] - vertexPosition.xy;
	}
}