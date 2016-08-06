#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;
in vec2 toLightVector[4];

out vec4 outColor;

uniform sampler2D spriteTexture;
uniform vec4 lightColor[4];
uniform float lightIntensity[4];
uniform float lightSize[4];
uniform float ambientFactor;

void main()
{
	vec3 ambient = vec3(1.0, 1.0, 1.0);
	vec4 totalLight;
	float lightDist;
	float attenuationFactor;
	
	for(int i = 0; i < 4; i++) {
		lightDist = length(toLightVector[i]);
		attenuationFactor = lightIntensity[i] / ((lightDist/lightSize[i] + 1.0) * (lightDist/lightSize[i] + 1.0));
		attenuationFactor = max(attenuationFactor, 0.0);
		totalLight = totalLight + lightColor[i] * attenuationFactor;
	}
	
	vec4 sprColor = fragmentColor * texture(spriteTexture, fragmentUV);
	vec4 finalAmbient = vec4(ambient * ambientFactor, 1.0);
	outColor = sprColor * (finalAmbient + totalLight);
}