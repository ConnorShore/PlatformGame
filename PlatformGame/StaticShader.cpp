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
}

void StaticShader::loadTexture()
{
	glUniform1i(_textureLoc, 0);
}

void StaticShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}
