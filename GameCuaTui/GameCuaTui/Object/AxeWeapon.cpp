#include "AxeWeapon.h"

AxeWeapon::AxeWeapon(int x, int y, bool direct) : Weapon(AXE)
{
	_comeBack = false;
	_sprite = SpriteManager::getInstance()->getSprite(WEAPON);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::WEAPON, "axe_1"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::WEAPON, "axe_1", "axe_2", "axe_3", "axe_4", NULL);

	auto move = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = move;

	if (direct)
	{
		move->setVelocity(GVector2(FLYING_SPEED, 440));
		move->setAccelerate(GVector2(-100,-800));
	}
	else
	{
		_sprite->setScaleX(-1);
		move->setVelocity(GVector2(-FLYING_SPEED, 440));
		move->setAccelerate(GVector2(100, -800));
	}
}

void AxeWeapon::ComeBack()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(move->getVelocity().x*(-1), move->getVelocity().y));
	_comeBack = true;
}


bool AxeWeapon::IsBoomerangComeBack()
{
	return _comeBack;
}


void AxeWeapon::release()
{
}

void AxeWeapon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

CollisionBody* AxeWeapon::getCollisionBody()
{
	return (CollisionBody*)_componentList["CollisionBody"];
}

void AxeWeapon::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void AxeWeapon::update(float deltatime)
{
	_animation->update(deltatime);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}
