#include "Soldier.h"


Soldier::Soldier(int x, int y, int activeX) : BaseObject(SOLDIER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::SOLDIER);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::SOLDIER, "soldier_01"));
	_sprite->setPosition(x, y);
	_sprite->setScale(2.0);
	_animation = new Animation(_sprite, 0.2f);
	_activeXLeft = activeX;
	_activeXRight = x;
	_animation->addFrameRect(eID::SOLDIER, "soldier_01", "soldier_02", "soldier_03", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	_effectAnimation = new Animation(_effect, 0.15f);
	_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", "hit_effect_4", NULL);

	_hitPoint = 2;
}

void Soldier::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
	{
		_effectAnimation->draw(spriteHandle, viewport);
	}
}

void Soldier::update(float deltatime)
{
	_effect->setPosition(this->getPosition());
	if (_hitPoint > 0)
	{
		_animation->update(deltatime);
		auto move = (Movement*)this->_componentList["Movement"];
		if (_startHit)
		{
			if (_hitStopWatch->isStopWatch(400))
			{
				_startHit = false;
				_hitStopWatch->restart();
			}
		}
		if (_startHit)
		{
			move->setVelocity(GVector2(0, 0));
		}
		else if (this->getPositionX() < _activeXLeft)
		{
			move->setVelocity(GVector2(SOLDIER_MOVE_SPEED, 0));
			
			if (this->_sprite->getScale().x > 0)
				this->_sprite->setScaleX(this->_sprite->getScale().x * (-1));
		}
		else if (this->getPositionX() > _activeXRight)
		{
			move->setVelocity(GVector2(-SOLDIER_MOVE_SPEED, 0));
			if (this->_sprite->getScale().x < 0)
				this->_sprite->setScaleX(this->_sprite->getScale().x * (-1));
		}
		else
		{
			if (this->_sprite->getScale().x < 0)
				move->setVelocity(GVector2(SOLDIER_MOVE_SPEED, 0));
			else
				move->setVelocity(GVector2(-SOLDIER_MOVE_SPEED, 0));
		}
	}
	else
	{
		_effectAnimation->update(deltatime);
		if (_effectStopWatch->isStopWatch(600))
		{
			this->setStatus(DESTROY);
			srand(time(0));
			auto ran = rand() % 10;
			BaseObject* heart = nullptr;
			if (ran < 3)
				heart = new Heart(this->getPositionX(), this->getPositionY() + 32);
			else
				heart = new Heart(this->getPositionX(), this->getPositionY() + 32);

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

	auto movement = new Movement(GVector2(0, 0), GVector2(-SOLDIER_MOVE_SPEED, 0), _sprite);
	_componentList["Movement"] = movement;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHit = false;
}

void Soldier::wasHit(int hitpoint)
{
	if (!_startHit)
	{
		_hitPoint -= hitpoint;
		_hitStopWatch->restart();
		_hitStopWatch->isTimeLoop(400);
		_startHit = true;
	}

	if (_hitPoint <= 0)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
		_effectStopWatch->isTimeLoop(600);
	}
}

bool Soldier::isDead()
{
	return (_hitPoint <= 0);
}
