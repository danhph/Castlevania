#include "Candle.h"

Candle::Candle(int x, int y): BaseObject(CANDLE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::CANDLE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::CANDLE, "candle_01"));
	_sprite->setPosition(x, y);
	_sprite->setScale(2.0);
	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::CANDLE, "candle_01", "candle_02", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	_effect->setPosition(x, y);
	_effectAnimation = new Animation(_effect, 0.1f);
	_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", "hit_effect_4", NULL);

	_wasHit = false;
}

void Candle::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (!_wasHit)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Candle::update(float deltatime)
{
	if (!_wasHit)
		_animation->update(deltatime);
	else
	{
		_effectAnimation->update(deltatime);
		if (_stopwatch->isStopWatch(400))
		{
			this->setStatus(DESTROY);
			srand(time(0));
			auto ran = rand() % 10;
			BaseObject* heart = nullptr;
			if (ran < 3)
				heart = new BigHeart(this->getPositionX(), this->getPositionY());
			else
				heart = new Heart(this->getPositionX(), this->getPositionY());
			
			if (heart != nullptr)
			{
				heart->init();
				QuadTreeNode::getInstance()->Insert(heart);
			}
		}
	}
}

void Candle::release()
{
	SAFE_DELETE(_effectAnimation);
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Candle::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_stopwatch = new StopWatch();
}

RECT Candle::getBounding()
{
	return _sprite->getBounding();
}

void Candle::wasHit()
{
	_wasHit = true;
	_stopwatch->isTimeLoop(400);
}

bool Candle::checkWasHit()
{
	return _wasHit;
}
