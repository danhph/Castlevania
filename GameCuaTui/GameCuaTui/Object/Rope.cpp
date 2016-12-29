#include "Rope.h"

Rope::Rope(int x, int y) : BaseObject(ROPE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ROPE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ROPE, "rope_13"));
	_sprite->setPosition(x, y);

	_animations[0] = new Animation(_sprite, 0.2f);
	_animations[0]->addFrameRect(eID::ROPE, "rope_11", "rope_12", "rope_13", "rope_13", NULL);

	_animations[1] = new Animation(_sprite, 0.2f);
	_animations[1]->addFrameRect(eID::ROPE, "rope_21", "rope_22", "rope_23", "rope_23", NULL);

	_animations[2] = new Animation(_sprite, 0.2f);
	_animations[2]->addFrameRect(eID::ROPE, "rope_31", "rope_32", "rope_33", "rope_33", NULL);

	_animations[3] = new Animation(_sprite, 0.2f);
	_animations[3]->addFrameRect(eID::ROPE, "rope_41", "rope_42", "rope_43", "rope_43", NULL);

	_animations[4] = new Animation(_sprite, 0.2f);
	_animations[4]->addFrameRect(eID::ROPE, "rope_51", "rope_52", "rope_53", "rope_53", NULL);

	_currentRope = 0;

	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void Rope::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations[_currentRope]->draw(spriteHandle, viewport);
}

void Rope::update(float deltatime)
{
	_animations[_currentRope]->update(deltatime);
}

void Rope::release()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_animations.clear();

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Rope::init()
{
}

float Rope::checkCollision(BaseObject* object, float dt)
{
	return 0.0f;
}

void Rope::updateRopePos(GVector2 pos)
{
	if (this->getScale().x > 0)
	{
		switch (_animations[_currentRope]->getIndex())
		{
			case 0:
				this->setPosition(pos + GVector2(-24, 28));
				break;
			case 1:
				this->setPosition(pos + GVector2(-16, 40));
				break;
			default:
				this->setPosition(pos + GVector2(20+ this->_sprite->getFrameWidth() / 2, 38));
				break;
		}
	}
	else
	{
		switch (_animations[_currentRope]->getIndex())
		{
			case 0:
				this->setPosition(pos + GVector2(24, 28));
				break;
			case 1:
				this->setPosition(pos + GVector2(16, 40));
				break;
			default:
				this->setPosition(pos + GVector2(-20 - this->_sprite->getFrameWidth() / 2, 38));
				break;
		}
	}
}

void Rope::restart()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		it->second->restart();
	}
}

RECT Rope::getBounding()
{
	if (_animations[_currentRope]->getIndex() > 1)
		return _sprite->getBounding();
	else
	{
		RECT rect;
		rect.left = 0;
		rect.bottom = 0;
		rect.top = 0;
		rect.right = 0;
		return rect;
	}
}

void Rope::resetRope()
{
	_currentRope = 0;
	this->setRope(_currentRope);
}


void Rope::setRope(int id)
{
	switch (id)
	{
		case 1:
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ROPE, "rope_23"));
			break;
		case 2:
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ROPE, "rope_33"));
			break;
		case 3:
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ROPE, "rope_43"));
			break;
		case 4:
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ROPE, "rope_53"));
			break;
		default:
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ROPE, "rope_13"));
			break;
	}
}

void Rope::upgradeRope()
{
	if (_currentRope < _animations.size() - 1)
	{
		_currentRope++;
		this->setRope(_currentRope);
	}
}

CollisionBody* Rope::getCollisionBody()
{
	return (CollisionBody*)_componentList["CollisionBody"];
}
