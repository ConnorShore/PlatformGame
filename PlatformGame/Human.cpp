#include "Human.h"
#include "ResourceManager.h"

#include <iostream>

Human::Human()
{
}


Human::~Human()
{
}

void Human::humanInit(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::ivec2& sheetDims, const std::string& texPath)
{
	_texture = ResourceManager::loadTexture(texPath);
	_dimension = dimension;
	_collisionCategory = CATEGORY_FRIENDLY;
	_collisionMask = MASK_FRIENDLY;

	_spritesheet.init(_texture, sheetDims);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.25f;
	fixtureDef.filter.categoryBits = _collisionCategory;
	fixtureDef.filter.maskBits = _collisionMask;
	_fixture = _body->CreateFixture(&fixtureDef);

	init();
}

void Human::humanUpdate()
{
	for (b2ContactEdge* ce = _body->GetContactList(); ce != nullptr; ce = ce->next) {
		b2Contact* c = ce->contact;
		if (c->IsTouching()) {
			b2WorldManifold manifold;
			c->GetWorldManifold(&manifold);

			//Check if points are below
			_canJump = false;
			for (int i = 0; i < b2_maxManifoldPoints; i++) {
				if (manifold.points[i].y < _body->GetPosition().y - _dimension.y / 2.0f + 0.01f) {
					//Add in capsule hit box for agents
					_canJump = true;
					break;
				}
			}

		//Can jump
		if (_canJump && _body->GetLinearVelocity().y < 0.0f)
			_onGround = true;
		}
	}

	update();
}

void Human::humanRender(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;
	glm::vec4 uvRect = animate();

	spriteBatch.addToBatch(destRect, uvRect, 1.0f, _texture.id, Color(255, 255, 255, 255));

	_currentWeapon->render(spriteBatch);

	render();
}

void Human::addWeapon(Weapon * weapon)
{
	weapon->setParent(this);
	weapon->getBulletDef().collisionCategory = _collisionCategory;
	weapon->getBulletDef().collisionMask = _collisionMask;

	if (_weapons.size() == 0) {
		_primaryWeapon = weapon;
		_secondaryWeapon = weapon;
		_currentWeapon = _primaryWeapon;
	}
	else if (_weapons.size() == 1) {
		_secondaryWeapon = weapon;
	}

	_weapons.push_back(weapon);
}

void Human::jump()
{
}
