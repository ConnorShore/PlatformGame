#pragma once

#include <CandleLight_Engine\ShaderProgram.h>

#include <string>

class GUIShader : public ShaderProgram
{
public:
	GUIShader();
	~GUIShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadTexture();
	void loadPMatrix(glm::mat4 matrix);

private:
	GLuint _textureLoc, _pMatrixLoc;
};