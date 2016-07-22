#include "GridShader.h"



GridShader::GridShader()
{
}

GridShader::~GridShader()
{
}

void GridShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexUV");
}

void GridShader::getUniformLocations()
{
	_pMatrixLoc = getUniformLocation("pMatrix");
}

void GridShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}
