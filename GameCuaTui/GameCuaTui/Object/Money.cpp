#include "Money.h"

Money::Money(int x, int y, int type) : BaseObject(MONEY)
{
	_type = type;


	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	switch (_type)
	{
	case 1:
		_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "blue_money"));
		break;
	case 2:
		_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "yellow_money"));
		break;
	default:
		_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "red_money"));
		break;
	}
	_sprite->setPosition(x, y);
	
	_stop = false;
}

int Money::GetCoin()
{
	switch (_type)
	{
		case 1: return 400;
		case 2: return 700;
		default: return 100;
	}
}


void Money::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void Money::update(float deltatime)
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

void Money::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Money::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	movement->setVelocity(GVector2(0, -200));
	_componentList["Movement"] = movement;

	_destroyStopWatch = new StopWatch();
	_startDestroyStopWatch = false;
}

RECT Money::getBounding()
{
	return _sprite->getBounding();
}


float Money::checkCollision(BaseObject* object, float dt)
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
