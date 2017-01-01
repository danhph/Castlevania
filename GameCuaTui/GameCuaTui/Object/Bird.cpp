#include "Bird.h"

Bird::Bird(int x, int y, bool direct) : BaseObject(BIRD)
{
	_initX = x;

	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "bird_1"));
	_sprite->setPosition(x, y);
	
	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::ENEMY, "bird_1", "bird_2", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	_effectAnimation = new Animation(_effect, 0.15f);
	_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", "hit_effect_4", NULL);

	_isDead = false;
	
	auto move = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = move;

	SinMovement* sinmovement = new SinMovement(GVector2(0,90), 0.5, _sprite);
	this->_componentList["SinMovement"] = sinmovement;

	if (direct)
	{
		_sprite->setScaleX(-1);
		move->setVelocity(GVector2(BIRD_MOVE_SPEED, 0));
	}
	else
	{
		move->setVelocity(GVector2(-BIRD_MOVE_SPEED, 0));
	}
}

void Bird::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_isDead)
		_effectAnimation->draw(spriteHandle, viewport);
	else
	{
		_animation->draw(spriteHandle, viewport);	
	}

}

void Bird::update(float deltatime)
{
	if (this->getPositionX() < _initX - 500 || this->getPositionX() > _initX + 500)
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
				heart = new Heart(this->getPositionX(), this->getPositionY());

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

void Bird::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Bird::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
}

void Bird::wasHit()
{
	_isDead = true;

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, 0));
	_effectStopWatch->isTimeLoop(600);
}

bool Bird::isDead()
{
	return _isDead;
}