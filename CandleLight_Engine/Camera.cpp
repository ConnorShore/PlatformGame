#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera() : _screenWidth(1280), _screenHeight(720), _needsUpdating(true), _position(0.0f, 0.0f), _orthoMatrix(1.0f), _cameraMatrix(1.0f), _scale(30.0f)
{
}


Camera::~Camera()
{
}

void Camera::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_orthoMatrix = glm::ortho(0.0f, (float) _screenWidth, 0.0f, (float) _screenHeight);
}

void Camera::update()
{
	if (_needsUpdating) {
		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsUpdating = false;
	}
}

glm::vec2 Camera::screenToWorldCoords(glm::vec2 screenCoords)
{
	// Invert Y direction
	screenCoords.y = _screenHeight - screenCoords.y;
	// Make it so that 0 is the center
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	// Scale the coordinates
	screenCoords /= _scale;
	// Translate with the camera position
	screenCoords += _position;
	return screenCoords;
}
