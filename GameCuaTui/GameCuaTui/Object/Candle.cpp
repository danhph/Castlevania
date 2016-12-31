#include "Candle.h"

Candle::Candle(int x, int y, eID item): BaseObject(CANDLE)
{
	_item = item;
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
			BaseObject* item = nullptr;
			if (_item == ITEM)
			{
				srand(time(0));
				auto ran = rand() % 20;
				if (ran < 5)
					item = new Money(this->getPositionX(), this->getPositionY(), ran % 3);
				else if (ran < 10)
					item = new BigHeart(this->getPositionX(), this->getPositionY());
				else if (ran == 10 || ran == 15)
					item = new RopeUpgrade(this->getPositionX(), this->getPositionY());
				else if (ran < 17)
					item = new Heart(this->getPositionX(), this->getPositionY());
			}
			else
			{
				switch (_item)
				{
				case ROPE_UPGRADE:
					item = new RopeUpgrade(this->getPositionX(), this->getPositionY());
					break;
				case DAGGER:
					item = new Dagger(this->getPositionX(), this->getPositionY());
					break;
				case BOOMERANG:
					item = new Boomerang(this->getPositionX(), this->getPositionY());
					break;
				case AXE:
					item = new Axe(this->getPositionX(), this->getPositionY());
					break;
				case POTION:
					item = new Potion(this->getPositionX(), this->getPositionY());
					break;
				case CROSS:
					item = new Cross(this->getPositionX(), this->getPositionY());
					break;
				default:
					item = new Heart(this->getPositionX(), this->getPositionY());
					break;
				}
			}
			if (item != nullptr)
			{
				item->init();
				QuadTreeNode::getInstance()->Insert(item);
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
