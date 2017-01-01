#include "Medusa.h"

Medusa::Medusa(int x, int y, int checkPoint, eID next) : BaseObject(MEDUSA)
{
	_next = next;
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS, "medusa_5"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::BOSS, "medusa_1", "medusa_2", "medusa_3", "medusa_4", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "fire_1"));
	_effectAnimation = new Animation(_effect, 0.15f);
	_effectAnimation->addFrameRect(EFFECT, "fire_1", "fire_2", "fire_3", "fire_4", NULL);

	_isDead = false;
	_isActive = false;
	_initX = x;
	_initY = y;

	_checkPoint = checkPoint;
	_playerDirect = false;
	_isDelayMove = false;
	_startHit = false;
	_hitpoint = 16;
}

void Medusa::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_isDead)
		_effectAnimation->draw(spriteHandle, viewport);
	else
	{
		if (_isActive)
			_animation->draw(spriteHandle, viewport);
		else
			_sprite->render(spriteHandle, viewport);
	}
}

void Medusa::update(float deltatime)
{
	if (_hitpoint <= 0 && !_isDead)
	{
		_isDead = true;
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
		_effectStopWatch->isTimeLoop(800);
	}

	if (!_isDead)
	{
		if (_isActive)
			if (_initSnakeStopWatch->isTimeLoop(2000))
			{
				auto x = this->getPositionX();
				if (abs(x - _initX) > 150)
					x = x / abs(x) * 150 + _initX;
				auto snake = new Snake(x, _initY, _playerDirect);
				snake->init();
				QuadTreeNode::getInstance()->Insert(snake);
			}
		if (_isDelayMove)
		{
			if (_stopStopWatch->isStopWatch(MEDUSA_MOVE_DELAY))
			{
				_isDelayMove = false;
				if (!_isActive)
				{
					_isActive = true;
					SinMovement* sinmovement = new SinMovement(MEDUSA_AMPLITUDE, 0.5, _sprite);
					this->_componentList["SinMovement"] = sinmovement;
					_initSnakeStopWatch->isTimeLoop(MEDUSA_SNAKE_DELAY);
				}

				auto move = (Movement*)this->_componentList["Movement"];
				if (_playerDirect)
					move->setVelocity(GVector2(MEDUSA_MOVE_SPEED, 0));
				else
					move->setVelocity(GVector2(-MEDUSA_MOVE_SPEED, 0));
			}
		}
		else
		{
			if (this->getPositionX() < _initX - 220 || this->getPositionX() > _initX + 220)
				this->DelayMove();
		}
		if (_startHit && _hitStopWatch->isStopWatch(400))
		{
			_startHit = false;
			_hitStopWatch->restart();
		}

		if (_isActive)
			_animation->update(deltatime);
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);
		if (_effectStopWatch->isStopWatch(800))
		{
			this->setStatus(DESTROY);
			auto viewportPos = SceneManager::getInstance()->getCurrentScene()->getViewport()->getPositionWorld();
			auto item = new Ball(viewportPos.x + 256, viewportPos.y - 200, _next);

			item->init();
			QuadTreeNode::getInstance()->Insert(item);
		}
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		if (it->second->GetName() == "SinMovement" && _isDelayMove)
			continue;
		it->second->update(deltatime);
	}
}

void Medusa::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Medusa::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	_effectStopWatch = new StopWatch();
	_initSnakeStopWatch = new StopWatch();
	_stopStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
}

void Medusa::wasHit()
{
	if (!_startHit)
	{
		_hitpoint -= 2;
		_hitStopWatch->restart();
		_hitStopWatch->isTimeLoop(400);
		_startHit = true;
	}
}

int Medusa::GetHitPoint()
{
	return _hitpoint;
}


bool Medusa::isDead()
{
	return _isDead;
}

void Medusa::Active()
{
	if (!_isDelayMove)
	{
		_isDelayMove = true;
		_stopStopWatch->isTimeLoop(MEDUSA_INIT_DELAY);
	}
}


bool Medusa::isActive()
{
	return _isActive;
}

int Medusa::getCheckPoint()
{
	return _checkPoint;
}

bool Medusa::GetDirect()
{
	return _playerDirect;
}

void Medusa::SetDirect(bool direct)
{
	_playerDirect = direct;
}

void Medusa::DelayMove()
{
	if (!_isDelayMove)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));

		_isDelayMove = true;
		_stopStopWatch->restart();
		_stopStopWatch->isTimeLoop(MEDUSA_MOVE_DELAY);
	}
}

bool Medusa::IsDelayMove()
{
	return _isDelayMove;
}
