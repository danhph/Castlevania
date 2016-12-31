#include "Frog.h"


Frog::Frog(int x, int y) : BaseObject(FROG)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "frog_1"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::ENEMY, "frog_1", "frog_2", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	_effectAnimation = new Animation(_effect, 0.15f);
	_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", "hit_effect_4", NULL);

	_isDead = false;
	_initX = x;
}

void Frog::MoveToPlayer(GVector2 pos)
{
	pos.y += 32;
	auto vec = pos - this->getPosition();
	if (vec.x != 0)
	{
		vec.y = vec.y / abs(vec.x) * FROG_MOVE_SPEED;

		if (vec.x > 0)
			vec.x = FROG_MOVE_SPEED;
		else
			vec.x = -FROG_MOVE_SPEED;
	}
	else
		vec.y = vec.y / abs(vec.y) * FROG_MOVE_SPEED;

	auto move = (Movement*) _componentList["Movement"];
	move->setVelocity(vec);

	if (vec.x < 0)
		_sprite->setScaleX(1);
	else
		_sprite->setScaleX(-1);
}


void Frog::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (!_isDead)
		_animation->draw(spriteHandle, viewport);
	else
	{
		_effectAnimation->draw(spriteHandle, viewport);
	}
}

void Frog::update(float deltatime)
{
	if (this->getPositionX() < _initX - 520 || this->getPositionX() > _initX + 520)
	{
		this->setStatus(DESTROY);
		return;
	}

	if (!_isDead)
	{
		_animation->update(deltatime);
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);
		if (_effectStopWatch->isStopWatch(600))
		{
			this->setStatus(DESTROY);
			srand(time(0));
			auto ran = rand() % 10;
			BaseObject* heart = nullptr;
			if (ran < 3)
				heart = new BigHeart(this->getPositionX(), this->getPositionY() + 32);
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

void Frog::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Frog::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(-FROG_MOVE_SPEED, 0), _sprite);
	_componentList["Movement"] = movement;

	auto move = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = move;

	_effectStopWatch = new StopWatch();
}

void Frog::wasHit()
{
	_isDead = true;

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, 0));
	_effectStopWatch->isTimeLoop(600);
}

bool Frog::isDead()
{
	return _isDead;
}
