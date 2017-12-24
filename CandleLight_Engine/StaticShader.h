#pragma once

#include "ShaderProgram.h"

#include <string>
#include <vector>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadTexture();
	void loadPMatrix(glm::mat4 matrix);
	void loadAmbient(glm::vec4& val);
	void loadResolution(glm::vec2& resolution);

private:
	GLuint _textureLoc, _lightMapLoc, _pMatrixLoc, _ambientLoc, _resolutionLoc;
};