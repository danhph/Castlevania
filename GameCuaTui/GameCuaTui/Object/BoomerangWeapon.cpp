#include "BoomerangWeapon.h"

BoomerangWeapon::BoomerangWeapon(int x, int y, bool direct) : Weapon(BOOMERANG)
{
	_comeBack = false;
	_sprite = SpriteManager::getInstance()->getSprite(WEAPON);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::WEAPON, "cross_1"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::WEAPON, "cross_1", "cross_2", "cross_3", NULL);

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

void BoomerangWeapon::ComeBack()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(move->getVelocity().x*(-1), move->getVelocity().y));
	_comeBack = true;
}


bool BoomerangWeapon::IsBoomerangComeBack()
{
	return _comeBack;
}


void BoomerangWeapon::release()
{
}

void BoomerangWeapon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

CollisionBody* BoomerangWeapon::getCollisionBody()
{
	return (CollisionBody*)_componentList["CollisionBody"];
}

void BoomerangWeapon::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void BoomerangWeapon::update(float deltatime)
{
	_animation->update(deltatime);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}
