#pragma once

#include "ShaderProgram.h";
#include "Light.h"

#include <string>
#include <vector>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadAmbientFactor(float factor);
	void loadTexture();
	void loadPMatrix(glm::mat4 matrix);
	void loadLights(std::vector<Light>& lights);

private:
	GLuint _textureLoc, _pMatrixLoc, _ambientFactorLoc;
	GLuint _lightIntensityLoc[4], _lightColorLoc[4], _lightSizeLoc[4], _lightPositionLoc[4];
	const int MAX_LIGHTS = 4;
};