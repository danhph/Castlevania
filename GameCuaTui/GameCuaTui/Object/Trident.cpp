#include "Trident.h"

Trident::Trident(int x, int y, bool full) : BaseObject(TRIDENT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::OBJECTS);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::OBJECTS, "trident_7"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.4f);

	_full = full;
	if (full)
		_animation->addFrameRect(eID::OBJECTS, "trident_7", "trident_6", "trident_5", "trident_4", "trident_3", "trident_2", "trident_1", "trident_1", NULL);
	else
		_animation->addFrameRect(eID::OBJECTS, "trident_4", "trident_3", "trident_2", "trident_1", "trident_1", NULL);
}

void Trident::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Trident::update(float deltatime)
{
	_animation->update(deltatime);
}

void Trident::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Trident::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

RECT Trident::getBounding()
{
	auto rect = _sprite->getBounding();
	
		rect.bottom += _animation->getIndex() * 16;
	if(!_full)
		rect.bottom += 16*3;
	return rect;
}
