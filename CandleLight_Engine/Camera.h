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

	glm::vec2 getPosition() const { return _position; }
	glm::mat4 getCameraMatrix() const { return _cameraMatrix; }
	float getScale() const { return _scale; }

	void setPosition(glm::vec2 newPos) { _position = newPos; _needsUpdating = true; }
	void setScale(float newScale) { _scale = newScale; _needsUpdating = true; }

private:
	int _screenWidth, _screenHeight;
	bool _needsUpdating;
	glm::vec2 _position;
	glm::mat4 _orthoMatrix, _cameraMatrix;
	float _scale;
};