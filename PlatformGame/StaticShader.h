#pragma once

#include "ShaderProgram.h"

#include <string>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadTexture();
	void loadPMatrix(glm::mat4 matrix);

private:
	GLuint _textureLoc, _pMatrixLoc;
};