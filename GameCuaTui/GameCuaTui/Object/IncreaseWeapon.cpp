#include "IncreaseWeapon.h"

IncreaseWeapon::IncreaseWeapon(int x, int y) : BaseObject(INCREASE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setPosition(x, y);
	_initX = x;
	_stop = false;
}

void IncreaseWeapon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void IncreaseWeapon::update(float deltatime)
{
	if (_startDestroyStopWatch)
	{
		if (_destroyStopWatch->isStopWatch(2000))
		{
			this->setStatus(DESTROY);
		}
	}

	auto move = (Movement*)this->_componentList["Movement"];
	if (_stop)
	{
		move->setVelocity(GVector2(0, 0));
	}
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void IncreaseWeapon::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void IncreaseWeapon::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	movement->setVelocity(GVector2(0, -200));
	_componentList["Movement"] = movement;

	_destroyStopWatch = new StopWatch();
	_startDestroyStopWatch = false;
}

RECT IncreaseWeapon::getBounding()
{
	return _sprite->getBounding();
}


float IncreaseWeapon::checkCollision(BaseObject* object, float dt)
{
	if (object->getId() == WALL)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			if (direction == TOP)
			{
				float moveX, moveY;
				if (collisionBody->isColliding(object, moveX, moveY, dt))
				{
					collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
				}
				if (!_startDestroyStopWatch)
				{
					_destroyStopWatch->isTimeLoop(ITEM_DESTROY_TIME);
					_startDestroyStopWatch = true;
				}
				_stop = true;
			}
			return 1.0f;
		}
	}
	return 0;
}
void IncreaseWeapon::setNum(int num)
{
	if (num == 1)
		_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "small2"));
	else if (num == 2)
		_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "small3"));
	else
		_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "small_heart"));
}
