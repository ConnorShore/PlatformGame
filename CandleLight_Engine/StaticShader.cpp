#include "StaticShader.h"



StaticShader::StaticShader()
{
	
}


StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexColor");
	bindAttribute(2, "vertexUV");
}

void StaticShader::getUniformLocations()
{
	_textureLoc = getUniformLocation("texture");
	_pMatrixLoc = getUniformLocation("pMatrix");
	_ambientFactorLoc = getUniformLocation("ambientFactor");

	for (int i = 0; i < 4; i++) {
		_lightPositionLoc[i] = getUniformLocation("lightPosition[" + std::to_string(i) + "]");
		_lightColorLoc[i] = getUniformLocation("lightColor[" + std::to_string(i) + "]");
		_lightIntensityLoc[i] = getUniformLocation("lightIntensity[" + std::to_string(i) + "]");
		_lightSizeLoc[i] = getUniformLocation("lightSize[" + std::to_string(i) + "]");
	}
}

void StaticShader::loadAmbientFactor(float factor)
{
	glUniform1f(_ambientFactorLoc, factor);
}

void StaticShader::loadTexture()
{
	glUniform1i(_textureLoc, 0);
}

void StaticShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}

void StaticShader::loadLights(std::vector<Light>& lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++) {
		if (i < lights.size()) {
			loadVector2f(_lightPositionLoc[i], lights[i].position);
			loadVector4f(_lightColorLoc[i], glm::vec4(lights[i].color.r, lights[i].color.g, lights[i].color.b, lights[i].color.a));
			loadFloat(_lightIntensityLoc[i], lights[i].intensity);
			loadFloat(_lightSizeLoc[i], lights[i].size);
		} else {
			loadVector2f(_lightPositionLoc[i], glm::vec2(0.0f));
			loadVector4f(_lightColorLoc[i], glm::vec4(0.0f));
			loadFloat(_lightIntensityLoc[i], 0.0f);
			loadFloat(_lightSizeLoc[i], 0.0f);
		}
	}
}
