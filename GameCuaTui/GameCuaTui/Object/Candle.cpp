#include "Candle.h"

Candle::Candle(int x, int y):BaseObject(CANDLE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::CANDLE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::CANDLE, "candle_01"));
	_sprite->setPosition(x, y);
	_sprite->setScale(2.0);
	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::CANDLE, "candle_01", "candle_02", NULL);
}

void Candle::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Candle::update(float deltatime)
{
	_animation->update(deltatime);

	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void Candle::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Candle::init()
{
	
}

RECT Candle::getBounding()
{
	return _sprite->getBounding();
}
