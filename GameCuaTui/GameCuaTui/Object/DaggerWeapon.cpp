#include "DaggerWeapon.h"

DaggerWeapon::DaggerWeapon(int x, int y, bool direct) : Weapon(DAGGER)
{
	_sprite = SpriteManager::getInstance()->getSprite(ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "dagger"));
	_sprite->setPosition(x, y);
	
	auto move = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = move;

	if (direct)
	{
		move->setVelocity(GVector2(FLYING_SPEED, 0));
	}
	else
	{
		_sprite->setScaleX(-1);
		move->setVelocity(GVector2(-FLYING_SPEED, 0));
	}
}
void DaggerWeapon::release()
{
}
void DaggerWeapon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

CollisionBody* DaggerWeapon::getCollisionBody()
{
	return (CollisionBody*)_componentList["CollisionBody"];
}
void DaggerWeapon::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}
void DaggerWeapon::update(float deltatime)
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}
