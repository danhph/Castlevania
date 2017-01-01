#include "Ball.h"

Ball::Ball(int x, int y, eID id) : BaseObject(BALL)
{
	_id = id;
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "ball_1"));
	_sprite->setPosition(x, y);
	_initX = x;
	_stop = false;

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "ball_1", "ball_2", NULL);

}

void Ball::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Ball::update(float deltatime)
{
	_animation->update(deltatime);

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

void Ball::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Ball::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	movement->setVelocity(GVector2(0, -200));
	_componentList["Movement"] = movement;
}

RECT Ball::getBounding()
{
	return _sprite->getBounding();
}


float Ball::checkCollision(BaseObject* object, float dt)
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
				_stop = true;
			}
			return 1.0f;
		}
	}
	return 0;
}

eID Ball::GetNext()
{
	return _id;
}
