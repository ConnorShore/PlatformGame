#pragma once

#include <CandleLight_Engine\ShaderProgram.h>

#include <string>

class GridShader : public ShaderProgram
{
public:
	GridShader();
	~GridShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadPMatrix(glm::mat4 matrix);

private:
	GLuint _pMatrixLoc;
};