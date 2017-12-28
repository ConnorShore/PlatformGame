#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void init(int screenWidth, int screenHeight);
	void update();

	glm::vec2 screenToWorldCoords(glm::vec2 screenCoords);
	glm::vec2 screenToGLCoords(glm::vec2 screenCoords);
	void createTransformMatrix();
	glm::vec2 pixelToGL(glm::vec2 pixelCoords);

	glm::vec2 getPosition() const { return _position; }
	glm::mat4 getCameraMatrix() const { return _cameraMatrix; }
	glm::mat4& getTransformationMatrix() { return _transformMatrix; }
	float getScale() const { return _scale; }

	void setPosition(glm::vec2 newPos) { _position = newPos; _needsUpdating = true; }
	void setScale(float newScale) { _scale = newScale; _needsUpdating = true; }

	inline int getScreenWidth() { return _screenWidth; }
	inline int getScreenHeight() { return _screenHeight; }

private:
	const int MAX_SCREEN_WIDTH = 2560;
	const int MAX_SCREEN_HEIGHT = 1440;
	float _screenScaleX, _screenScaleY;
	int _screenWidth, _screenHeight;
	bool _needsUpdating;
	glm::vec2 _position;
	glm::mat4 _orthoMatrix, _cameraMatrix, _transformMatrix;
	float _scale;
};