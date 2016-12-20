#include "Soldier.h"

Soldier::Soldier(int x, int y, int activeX) :BaseObject(SOLDIER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::SOLDIER);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::SOLDIER, "soldier_01"));
	_sprite->setPosition(x, y);
	_sprite->setScale(2.0);
	_animation = new Animation(_sprite, 0.15f);
	_activeXLeft = activeX;
	_activeXRight = x;
	_animation->addFrameRect(eID::SOLDIER, "soldier_01", "soldier_02", "soldier_03", NULL);
}

void Soldier::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Soldier::update(float deltatime)
{
	_animation->update(deltatime);

	if (this->getPositionX() < _activeXLeft || this->getPositionX() > _activeXRight)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(move->getVelocity().x *(-1) , 0));
		this->_sprite->setScaleX(this->_sprite->getScale().x*(-1));
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}

}

void Soldier::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Soldier::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(-80, 0), _sprite);
	_componentList["Movement"] = movement;
}