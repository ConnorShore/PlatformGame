#include "LightShader.h"



LightShader::LightShader()
{
}


LightShader::~LightShader()
{
}

void LightShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexColor");
	bindAttribute(2, "vertexUV");
}

void LightShader::getUniformLocations()
{
	_pMatrixLoc = getUniformLocation("pMatrix");
	_texLoc = getUniformLocation("lightTex");
}

void LightShader::loadTextures()
{
	glUniform1i(_texLoc, 0);
	//glUniform1i(_gColLoc, 1);
}

void LightShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}
