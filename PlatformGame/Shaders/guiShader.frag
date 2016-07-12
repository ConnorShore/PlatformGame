#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 outColor;

uniform sampler2D spriteTexture;

void main()
{
	outColor = fragmentColor * 	texture(spriteTexture, fragmentUV);
}