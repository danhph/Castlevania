#include "Snake.h"

Snake::Snake(int x, int y, bool direct) : BaseObject(SNAKE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS, "snake_1"));
	_sprite->setPosition(x, y);
	_initX = x;
	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::BOSS, "snake_1", "snake_2", NULL);
	
	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	_effectAnimation = new Animation(_effect, 0.15f);
	_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", "hit_effect_4", NULL);

	auto move = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = move;
	_direct = direct;
	if (direct)
	{
		_sprite->setScaleX(-1);
		move->setVelocity(GVector2(0, -200));
	}
	else
	{
		move->setVelocity(GVector2(0, -200));
	}

	_wasHit = false;

}

void Snake::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Snake::update(float deltatime)
{
	if (!_wasHit)
		_animation->update(deltatime);
	else
	{
		_effectAnimation->update(deltatime);
		if (_stopwatch->isStopWatch(400))
		{
			this->setStatus(DESTROY);
		}
	}
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Snake::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Snake::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_stopwatch = new StopWatch();
	
}

float Snake::checkCollision(BaseObject* object, float dt)
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
				auto move = (Movement*)this->_componentList["Movement"];
				auto x = SNAKE_MOVE_SPEED;
				if (!_direct)
					x = -x;
				move->setVelocity(GVector2(x, 0));
			}
			else
			{
				this->setStatus(DESTROY);
			}
			return 1.0f;
		}
	}
	return 0;
}

void Snake::wasHit()
{
	_wasHit = true;
	_stopwatch->isTimeLoop(400);
}

bool Snake::checkWasHit()
{
	return _wasHit;
}
