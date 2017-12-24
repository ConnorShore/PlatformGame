#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 outColor;

uniform sampler2D lightMap;
uniform sampler2D spriteTexture;

uniform vec2 resolution;
uniform vec4 ambient;

void main()
{
	vec2 lightCoord = gl_FragCoord.xy / resolution;
	vec4 diffuse = texture(spriteTexture, fragmentUV);
	vec4 lightColor = texture(lightMap, lightCoord);
	
	vec4 ambientColor = vec4(ambient.rgb * ambient.a, 1.0);
	vec3 intensity = ambientColor.rgb + lightColor.rgb;
	vec3 finalColor = diffuse.rgb * intensity;
	
	outColor = fragmentColor * vec4(finalColor, diffuse.a);
}