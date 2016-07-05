#include "Weapon.h"

#include <CandleLight_Engine\ResourceManager.h>

#include <glm\gtx\vector_angle.hpp>

Weapon::Weapon(const glm::vec2 & position, const glm::vec2& dimension, const glm::vec2& origin, const std::string & filePath) : _position(position), _dimension(dimension), _origin(origin / 10.0f), _angle(0)
{
	//Initialize position to player and remove parameter
	_texture = ResourceManager::loadTexture(filePath);
}

void Weapon::update(InputManager inputManager, Camera& camera)
{
	//glm::vec2 parent(_parent->getPosition());
	//_position = glm::vec2(parent.x + _origin.x, parent.y + _origin.y);

	//glm::vec2 mouse(camera.screenToWorldCoords(inputManager.getMousePos()));
	//_angle = (atan2(mouse.y - _position.y, mouse.x - _position.x));
	//
	//_bulletDef.direction = glm::vec2(glm::cos(_angle), glm::sin(_angle));
	//_bulletDef.position = glm::vec2(_position.x, _position.y) + _bulletDef.direction;

	//if (_fireCount < _fireRate) {
	//	_canShoot = false;
	//	_fireCount++;
	//} else {
	//	_canShoot = true;
	//}
}

void Weapon::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _position.x - _dimension.x / 2.0f;
	destRect.y = _position.y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;

	if (_parent->getDirection() == RIGHT) {
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		spriteBatch.addToBatch(destRect, uvRect, 1.0f, _texture.id, Color(255, 255, 255, 255), _angle, true);
	}
	else {
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, -1.0f);
		spriteBatch.addToBatch(destRect, uvRect, 1.0f, _texture.id, Color(255, 255, 255, 255), _angle, true);
	}
}

bool Weapon::shoot()
{
	if (_canShoot) {
		_fireCount = 0;
		_canShoot = false;
		return true;
	}
	return false;
}
