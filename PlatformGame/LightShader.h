#pragma once

#include <CandleLight_Engine\ShaderProgram.h>
#include <CandleLight_Engine\Light.h>

#include <string>
#include <vector>

class LightShader : public ShaderProgram
{
public:
	LightShader();
	~LightShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadTextures();
	void loadPMatrix(glm::mat4 matrix);

private:
	GLuint _texLoc, _pMatrixLoc;
};