#include "Treasure.h"


Treasure::Treasure(int x, int y, int initX, int initY) : BaseObject(TREASURE)
{
	_initX = initX;
	_initY = initY;

	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "box_yellow"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "box_yellow", "box_red", NULL);

	_active = false;
}

void Treasure::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_stopWatch = new StopWatch();
	_destroyStopWatch = new StopWatch();
	_startDestroyStopWatch = false;
}

void Treasure::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_active)
		_animation->draw(spriteHandle, viewport);
}

void Treasure::update(float deltatime)
{
	_animation->update(deltatime);

	if (_startDestroyStopWatch)
	{
		if (_destroyStopWatch->isStopWatch(ITEM_DESTROY_TIME * 2))
		{
			this->setStatus(DESTROY);
		}
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Treasure::Active(bool active)
{
	if (active == false)
		_stopWatch->restart();
	else if (!_active)
	{
		if (_stopWatch->isStopWatch(DELAY_SHOW))
		{
			_active = active;
			this->setPosition(_initX, _initY);
			if (!_startDestroyStopWatch)
			{
				_destroyStopWatch->isTimeLoop(ITEM_DESTROY_TIME * 2);
				_startDestroyStopWatch = true;
			}
		}
	}
}

bool Treasure::IsActive()
{
	return _active;
}


void Treasure::release()
{
}
