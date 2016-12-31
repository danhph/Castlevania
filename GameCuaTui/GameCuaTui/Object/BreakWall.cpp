#include "BreakWall.h"

BreakWall::BreakWall(int x, int y) : BaseObject(BREAKWALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::WALL);
	_sprite->setPosition(x, y);
	_sprite->setScale(2.0);
	
	_sprite2 = SpriteManager::getInstance()->getSprite(eID::WALL);
	_sprite2->setPosition(x, y + 32);
	_sprite2->setScale(2.0);

	_effect = SpriteManager::getInstance()->getSprite(eID::BREAKWALL);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BREAKWALL, "break_1"));
	_effect->setPosition(x, y + 32);
	_effectAnimation = new Animation(_effect, 0.08f);
	_effectAnimation->addFrameRect(BREAKWALL, "break_1", "break_2", "break_3", "break_4", "break_5", "break_6", "break_7", "break_8", "break_9", "break_10", NULL);

	_hitPoint = 2;
}

void BreakWall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint == 2)
	{
		_sprite->render(spriteHandle, viewport);
		_sprite2->render(spriteHandle, viewport);
	}
	else if (_hitPoint == 1)
	{
		_sprite->render(spriteHandle, viewport);
		if (_startHit)
			_effectAnimation->draw(spriteHandle, viewport);
	}
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void BreakWall::update(float deltatime)
{
	if (_startHit)
	{
		if (_hitStopWatch->isStopWatch(400))
		{
			_startHit = false;
			_hitStopWatch->restart();
		}
		_effectAnimation->update(deltatime);
	}

	if (_hitPoint == 0)
	{
		_effectAnimation->setPosition(_sprite->getPosition());
		if (_effectStopWatch->isStopWatch(600))
		{
			this->setStatus(DESTROY);
			BaseObject* heart = nullptr;
			if (heart != nullptr)
			{
				heart->init();
				QuadTreeNode::getInstance()->Insert(heart);
			}
		}
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void BreakWall::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void BreakWall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHit = false;
}

RECT BreakWall::getBounding()
{
	return _sprite->getBounding();
}

void BreakWall::wasHit()
{
	if (!_startHit)
	{
		_hitPoint -= 1;
		_hitStopWatch->restart();
		_hitStopWatch->isTimeLoop(600);
		_startHit = true;
	}

	if (_hitPoint <= 0)
	{
		_effectStopWatch->isTimeLoop(600);
	}
}

bool BreakWall::isBroken()
{
	return (_hitPoint <= 0);
}

void BreakWall::setColor(D3DXCOLOR color)
{
	_sprite->setColor(color);
	_sprite2->setColor(color);
}
