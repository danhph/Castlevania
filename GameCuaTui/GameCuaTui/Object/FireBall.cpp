#include "FireBall.h"

FireBall::FireBall(int x, int y, bool direct) :BaseObject(FIREBALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "fireball"));
	_sprite->setPosition(x, y);
	
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
	if (direct)
		movement->setVelocity(GVector2(FIREBALL_SPEED, 0));
	else
		movement->setVelocity(GVector2(-FIREBALL_SPEED, 0));

	_isDead = false;
}

void FireBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);

	if (!isIntersectedInGame(viewport->getBounding(), _sprite->getBounding()))
	{
		this->setStatus(DESTROY);
	}
}

void FireBall::update(float deltatime)
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void FireBall::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void FireBall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

bool FireBall::isDead()
{
	return _isDead;
}

void FireBall::wasHit()
{
	_isDead = true;
}

