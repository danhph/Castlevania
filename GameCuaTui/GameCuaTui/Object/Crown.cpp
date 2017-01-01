#include "Crown.h"


Crown::Crown(int x, int y, int initX, int initY) : BaseObject(CROWN)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "crown_yellow"));
	_sprite->setPosition(x, y);

	_initX = initX;
	_initY = initY;

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "crown_yellow", "crown_red", NULL);

	_active = false;
}


void Crown::release()
{
}

void Crown::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_active)
		_animation->draw(spriteHandle, viewport);
}

void Crown::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_destroyStopWatch = new StopWatch();
	_startDestroyStopWatch = false;
}

void Crown::update(float deltatime)
{
	_animation->update(deltatime);

	if (_startDestroyStopWatch)
	{
		if (_destroyStopWatch->isStopWatch(ITEM_DESTROY_TIME * 4))
		{
			this->setStatus(DESTROY);
		}
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Crown::Active(bool active)
{
	_active = true;
	this->setPosition(_initX, _initY);
	SoundManager::getInstance()->Play(HIDDEN_ITEM_APPEAR);
	if (!_startDestroyStopWatch)
	{
		_destroyStopWatch->isStopWatch(ITEM_DESTROY_TIME * 4);
		_startDestroyStopWatch = true;
	}
}

bool Crown::IsActive()
{
	return _active;
}

