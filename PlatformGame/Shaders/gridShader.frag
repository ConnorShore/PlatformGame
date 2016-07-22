#version 330 core

in vec4 fragmentPosition;

out vec4 outColor;

void main()
{
	if(fract(fragmentPosition.x/0.001) < 0.01 || fract(fragmentPosition.y / 0.001) < 0.01) {
		outColor = vec4(1);
	} else {
		outColor = vec4(0);
	}
}