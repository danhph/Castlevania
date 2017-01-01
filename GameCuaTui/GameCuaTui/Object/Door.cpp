#include "Door.h"

Door::Door(int x, int y) : BaseObject(DOOR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::OBJECTS);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::OBJECTS, "door_1"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::OBJECTS, "door_1", "start_open_1", "open_1", NULL);
	_animation->animateFromTo(0, 2, false);

	_closeAnimation = new Animation(_sprite, 0.2f);
	_closeAnimation->addFrameRect(eID::OBJECTS, "open_1", "start_open_1", "door_1", NULL);
	_closeAnimation->animateFromTo(0, 2, false);

	_wasOpen = false;
	_isClosing = false;
}

void Door::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_wasOpen)
	{
		if (_isClosing)
			_closeAnimation->draw(spriteHandle, viewport);
		else
			_animation->draw(spriteHandle, viewport);
	}
	else
		_sprite->render(spriteHandle, viewport);
}

void Door::update(float deltatime)
{
	if (_wasOpen)
	{
		_animation->update(deltatime);
		if (_stopwatch->isStopWatch(2000))
		{
			_isClosing = true;
		}
	}

	if (_isClosing)
	{
		_closeAnimation->update(deltatime);
	}
}

void Door::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Door::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
	_stopwatch = new StopWatch();
}

RECT Door::getBounding()
{
	RECT rect;
	if (!_wasOpen || _isClosing)
	{
		rect = _sprite->getBounding();
		rect.left -= 8;
		rect.right += 8;
		return rect;
	}
	else
	{
		rect.left = 0;
		rect.bottom = 0;
		rect.top = 0;
		rect.right = 0;
		return rect;
	}
}

void Door::Open()
{
	if (!_wasOpen)
	{
		SoundManager::getInstance()->Play(OPEN_DOOR);
		_wasOpen = true;
		_stopwatch->isTimeLoop(2000);
	}
}
