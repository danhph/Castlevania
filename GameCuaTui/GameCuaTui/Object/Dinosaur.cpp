#include "Dinosaur.h"

Dinosaur::Dinosaur(int x, int y) :BaseObject(DINOSAUR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "dinosaur_0"));
	_sprite->setPosition(x, y);
	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(ENEMY, "dinosaur_0", NULL);
	_animation->setValueFlashes(0.5);

	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	_effectAnimation = new Animation(_effect, 0.15f);
	_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", "hit_effect_4", NULL);
	_effect->setPosition(this->getPosition());

	_hitPoint = 6;
	_direct = false;
	_startHit = false;
	_ready = 0;
}

void Dinosaur::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Dinosaur::shoot()
{
	auto y = this->getPositionY();
	if (_direct)
		y -= 14;
	else
		y += 14;
	auto fireball = new FireBall(this->getPositionX(), y, _direct);
	fireball->init();
	QuadTreeNode::getInstance()->Insert(fireball);
}

void Dinosaur::setDirect(bool direct)
{
	_direct = direct;
}


void Dinosaur::update(float deltatime)
{
	_animation->update(deltatime);

	if (_hitPoint > 0)
	{
		if (_startHit)
		{
			if (_hitStopWatch->isStopWatch(400))
			{
				_startHit = false;
				_hitStopWatch->restart();
			}
		}

		if (_readyStopWatch->isTimeLoop(SHOOT_DELAY))
		{
			_ready = 30;
		}

		if (_ready > 0)
		{
			_animation->enableFlashes(true);
			_ready--;
		}
		else
			_animation->enableFlashes(false);

		if (_shoot1StopWatch->isTimeLoop(SHOOT_DELAY))
		{
			this->shoot();
		}

		if (_shoot2StopWatch->isTimeLoop(SHOOT_DELAY))
		{
			this->shoot();
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

void Dinosaur::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Dinosaur::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_readyStopWatch = new StopWatch();
	_shoot1StopWatch = new StopWatch();
	_shoot2StopWatch = new StopWatch();

	_readyStopWatch->isTimeLoop(0);
	_shoot1StopWatch->isTimeLoop(600);
	_shoot2StopWatch->isTimeLoop(1200);
}

bool Dinosaur::isDead()
{
	return (_hitPoint <= 0);
}

void Dinosaur::wasHit(int hitpoint)
{
	if (!_startHit)
	{
		_hitPoint -= hitpoint;
		_hitStopWatch->restart();
		_hitStopWatch->isTimeLoop(400);
		_startHit = true;
	}
}
