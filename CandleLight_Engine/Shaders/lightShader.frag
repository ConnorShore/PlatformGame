#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 outColor;

uniform sampler2D lightTex;

void main()
{
	outColor = fragmentColor * texture(lightTex, fragmentUV);
}