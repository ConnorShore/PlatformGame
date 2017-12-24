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
	_lightMapLoc = getUniformLocation("lightMap");
	_resolutionLoc = getUniformLocation("resolution");
	_ambientLoc = getUniformLocation("ambient");
}
void StaticShader::loadTexture()
{
	loadInt(_textureLoc, 0);
	loadInt(_lightMapLoc, 1);
}

void StaticShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}

void StaticShader::loadAmbient(glm::vec4& val)
{
	loadVector4f(_ambientLoc, val);
}

void StaticShader::loadResolution(glm::vec2 & resolution)
{
	loadVector2f(_resolutionLoc, resolution);
}
