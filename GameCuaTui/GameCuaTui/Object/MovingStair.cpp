#include "MovingStair.h"

void MovingStair::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

MovingStair::MovingStair(int x, int y, int activeX) : BaseObject(MOVING_STAIR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::OBJECTS);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::OBJECTS, "moving_stair"));
	_sprite->setPosition(x, y);
	_activeXLeft = activeX;
	_activeXRight = x;
}

void MovingStair::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(-STAIR_MOVE_SPEED, 0), _sprite);
	_componentList["Movement"] = movement;
}

void MovingStair::update(float deltatime)
{
	auto move = (Movement*)this->_componentList["Movement"];
	if (this->getPositionX() < _activeXLeft)
	{
		move->setVelocity(GVector2(STAIR_MOVE_SPEED, 0));
	}
	else if (this->getPositionX() > _activeXRight)
	{
		move->setVelocity(GVector2(-STAIR_MOVE_SPEED, 0));
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void MovingStair::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

GVector2 MovingStair::getVelocity()
{
	auto move = (Movement*)this->_componentList["Movement"];
	return move->getVelocity();
}
