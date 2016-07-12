#include "GUIShader.h"



GUIShader::GUIShader()
{

}


GUIShader::~GUIShader()
{
}

void GUIShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexColor");
}

void GUIShader::getUniformLocations()
{
	_textureLoc = getUniformLocation("texture");
	_pMatrixLoc = getUniformLocation("pMatrix");
}

void GUIShader::loadTexture()
{
	glUniform1i(_textureLoc, 0);
}

void GUIShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}
