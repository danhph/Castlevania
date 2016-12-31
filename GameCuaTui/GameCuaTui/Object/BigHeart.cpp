#include "BigHeart.h"

BigHeart::BigHeart(int x, int y) : BaseObject(BIGHEART)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "big_heart"));
	_sprite->setPosition(x, y);
	_initX = x;
	_stop = false;
}

void BigHeart::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void BigHeart::update(float deltatime)
{
	if (_startDestroyStopWatch)
	{
		if (_destroyStopWatch->isStopWatch(ITEM_DESTROY_TIME))
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

void BigHeart::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void BigHeart::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	movement->setVelocity(GVector2(0, -200));
	_componentList["Movement"] = movement;

	_destroyStopWatch = new StopWatch();
	_startDestroyStopWatch = false;
}

RECT BigHeart::getBounding()
{
	return _sprite->getBounding();
}


float BigHeart::checkCollision(BaseObject* object, float dt)
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
					_destroyStopWatch->isTimeLoop(2000);
					_startDestroyStopWatch = true;
				}
				_stop = true;
			}
			return 1.0f;
		}
	}
	return 0;
}