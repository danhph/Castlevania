#include "Player.h"
#include "../Framework/SceneManager.h"
#include "Stair.h"
#include "StairEnd.h"
#include <thread>

Player::Player(int life) : BaseObject(eID::PLAYER)
{
	_lifeNum = life;
}

Player::~Player()
{
}

void Player::init()
{
	__hook(&InputController::__eventkeyPressed, _input, &Player::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Player::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::PLAYER);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::PLAYER, "walk_right_01"));
	_sprite->setZIndex(1.0f);

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);

	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);

	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Player::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Player::onCollisionEnd);

	_rope = new Rope(0, 0);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::PLAYER, "walk_right_01", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.12f);
	_animations[eStatus::RUNNING]->addFrameRect(eID::PLAYER, "walk_right_01", "walk_right_02", "walk_right_03", NULL);

	_animations[eStatus::SIT_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SIT_DOWN]->addFrameRect(eID::PLAYER, "sit_down", NULL);

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::PLAYER, "jump", NULL);

	_animations[eStatus::FALLING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FALLING]->addFrameRect(eID::PLAYER, "walk_right_01", NULL);


	_animations[eStatus::MOVING_UP] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_UP]->addFrameRect(eID::PLAYER, "up", "walk_right_02", NULL);

	_animations[eStatus::MOVING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_DOWN]->addFrameRect(eID::PLAYER, "down", "walk_right_02", NULL);

	_animations[eStatus::STAND_UP] = new Animation(_sprite, 0.12f);
	_animations[eStatus::STAND_UP]->addFrameRect(eID::PLAYER, "up", NULL);

	_animations[eStatus::STAND_DOWN] = new Animation(_sprite, 0.12f);
	_animations[eStatus::STAND_DOWN]->addFrameRect(eID::PLAYER, "down",NULL);


	_animations[eStatus::ATTACKING] = new Animation(_sprite, 0.2f);
	_animations[eStatus::ATTACKING]->addFrameRect(eID::PLAYER, "stand_and_hit_01", "stand_and_hit_02", "stand_and_hit_03", "stand_and_hit_03", NULL);

	_animations[STAND_UP | ATTACKING] = new Animation(_sprite, 0.2f);
	_animations[STAND_UP | ATTACKING]->addFrameRect(eID::PLAYER, "up_and_hit_01", "up_and_hit_02", "up_and_hit_03", "up_and_hit_03", NULL);

	_animations[STAND_DOWN | ATTACKING] = new Animation(_sprite, 0.2f);
	_animations[STAND_DOWN | ATTACKING]->addFrameRect(eID::PLAYER, "down_and_hit_01", "down_and_hit_02", "down_and_hit_03", "down_and_hit_03", NULL);

	_animations[SIT_DOWN | ATTACKING] = new Animation(_sprite, 0.2f);
	_animations[SIT_DOWN | ATTACKING]->addFrameRect(eID::PLAYER, "jump_and_hit_01", "jump_and_hit_02", "jump_and_hit_03", "jump_and_hit_03", NULL);

	_animations[JUMPING | ATTACKING] = new Animation(_sprite, 0.2f);
	_animations[JUMPING | ATTACKING]->addFrameRect(eID::PLAYER, "jump_and_hit_01", "jump_and_hit_02", "jump_and_hit_03", "jump_and_hit_03", NULL);

	this->setOrigin(GVector2(0.5f, 0.0f));
	this->setStatus(eStatus::NORMAL);

	// create stopWatch
	_stopWatch = new StopWatch();
	_ropeStopWatch = new StopWatch();

	this->resetValues();

	_info = new Info();
	_info->SetHeart(0);
	_info->SetLife(3);
	_info->SetScore(0);
	_info->SetStage(0);
	_info->SetTime(0);
	_info->init();
}

void Player::update(float deltatime)
{
	this->checkPosition();

	if (_ropeStopWatch->isStopWatch(ATTACK_TIME) && _isAttacking)
	{
		_isAttacking = false;
		this->removeStatus(ATTACKING);
	}

	this->updateStatus(deltatime);

	this->updateCurrentAnimateIndex();

	_animations[_currentAnimateIndex]->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Player::updateInput(float dt)
{
}

GVector2 Player::getPosition()
{
	if (this->getStatus() != NORMAL)
	{
		if ((this->getStatus() & eStatus::JUMPING) == eStatus::JUMPING || (this->getStatus() & eStatus::SIT_DOWN) == eStatus::SIT_DOWN)
			return _sprite->getPosition() + GVector2(0, -16);
	}
	return _sprite->getPosition();
}


void Player::updateStatus(float dt)
{
	if (this->isInStatus(eStatus::DIE))
	{
		if (_lifeNum < 0)
		{
			return;
		}
		if (!_animations[eStatus::DIE]->isAnimate())
		{
			this->revive();
		}
		return;
	}
	if (_isAttacking)
	{
		_rope->setScaleX(this->_sprite->getScale().x);
		_rope->update(dt);
		_rope->updateRopePos(this->getPosition());
	}

	if ((this->getStatus() & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT)
	{
		this->moveLeft();
	}
	else if ((this->getStatus() & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT)
	{
		this->moveRight();
	}
	else if ((this->getStatus() & eStatus::SIT_DOWN) == eStatus::SIT_DOWN)
	{
		this->sitDown();
	}
	else if ((this->getStatus() & eStatus::FALLING) == eStatus::FALLING)
	{
		this->falling();
	}
	else if ((this->getStatus() & eStatus::MOVING_UP) == eStatus::MOVING_UP)
	{
		moveUp();
	}
	else if ((this->getStatus() & eStatus::MOVING_DOWN) == eStatus::MOVING_DOWN)
	{
		moveDown();
	}
	else if ((this->getStatus() & eStatus::STAND_DOWN) == eStatus::STAND_DOWN)
	{
		if (_input->isKeyDown(DIK_DOWN))
			this->setStatus(MOVING_DOWN);
	}
	else if ((this->getStatus() & eStatus::STAND_UP) == eStatus::STAND_UP)
	{
		if (_input->isKeyDown(DIK_UP))
			this->setStatus(MOVING_UP);
	}
	else if ((this->getStatus() & eStatus::JUMPING) != eStatus::JUMPING)
	{
		this->standing();
	}
}

void Player::updateCurrentAnimateIndex()
{
	_currentAnimateIndex = this->getStatus();

	if ((_currentAnimateIndex & eStatus::FALLING) == eStatus::FALLING)
	{
		_currentAnimateIndex = eStatus::FALLING;
	}

	if ((_currentAnimateIndex & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT || ((_currentAnimateIndex & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT))
	{
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex & ~(eStatus::MOVING_LEFT | MOVING_RIGHT));
		if ((_currentAnimateIndex & eStatus::MOVING_UP) == eStatus::MOVING_UP)
		{
			_currentAnimateIndex = eStatus::MOVING_UP;
		}
		else if ((_currentAnimateIndex & eStatus::MOVING_DOWN) == eStatus::MOVING_DOWN)
		{
			_currentAnimateIndex = eStatus::MOVING_DOWN;
		}
		else
			_currentAnimateIndex = (eStatus)(_currentAnimateIndex | eStatus::RUNNING);
	}


	if ((_currentAnimateIndex & eStatus::JUMPING) == eStatus::JUMPING)
	{
		if ((_currentAnimateIndex & eStatus::ATTACKING) != eStatus::ATTACKING)
			_currentAnimateIndex = eStatus::JUMPING;
	}


	if (this->isInStatus(eStatus::DIE))
	{
		_currentAnimateIndex = eStatus::DIE;
	}
}


void Player::resetValues()
{
	this->setScale(SCALE_FACTOR);
	_isAttacking = false;
	_stair = nullptr;
	_stairEnd = nullptr;
	_holdingKey = false;

	_movingSpeed = MOVE_SPEED;

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void Player::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations[_currentAnimateIndex]->draw(spriteHandle, viewport);

	if (_isAttacking)
	{
		_rope->draw(spriteHandle, viewport);
	}

	_info->draw(spriteHandle, viewport);
}

void Player::release()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_animations.clear();

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();

	SAFE_DELETE(_sprite);
	SAFE_DELETE(_stopWatch);
	SAFE_DELETE(_info);
	this->unhookinputevent();
}

void Player::onKeyPressed(KeyEventArg* key_event)
{
	if (this->isInStatus(eStatus::DIE))
		return;
	if (_isAttacking)
		return;
	switch (key_event->_key)
	{
		case DIK_LEFT:
			{
				if (this->isInStatus(SIT_DOWN))
				{
					if (this->getScale().x > 0)
						this->setScaleX(this->getScale().x * (-1));
					break;
				}
				if (this->isInStatus(STAND_UP) || this->isInStatus(MOVING_UP) || this->isInStatus(STAND_DOWN) || this->isInStatus(MOVING_DOWN))
					break;
				if (!this->isInStatus(eStatus::JUMPING))
				{
					this->removeStatus(eStatus::MOVING_RIGHT);
					this->addStatus(eStatus::MOVING_LEFT);
				}

				break;
			}
		case DIK_RIGHT:
			{
				if (this->isInStatus(SIT_DOWN))
				{
					if (this->getScale().x < 0)
						this->setScaleX(this->getScale().x * (-1));
					break;
				}
				if (this->isInStatus(STAND_UP) || this->isInStatus(MOVING_UP) || this->isInStatus(STAND_DOWN) || this->isInStatus(MOVING_DOWN))
					break;
				if (!this->isInStatus(eStatus::JUMPING))
				{
					this->removeStatus(eStatus::MOVING_LEFT);
					this->addStatus(eStatus::MOVING_RIGHT);
				}
				break;
			}
		case DIK_DOWN:
			{
				if (this->isInStatus(STAND_UP) || this->isInStatus(STAND_DOWN) || this->isInStatus(MOVING_DOWN) || this->isInStatus(MOVING_UP))
				{
					moveDown();
					_holdingKey = true;
				}
				else if (_stairEnd != nullptr)
				{
					moveDownToStair();
					_holdingKey = true;
				}
				else if (!this->isInStatus(eStatus::JUMPING))
				{
					this->addStatus(eStatus::SIT_DOWN);
					this->removeStatus(eStatus::MOVING_LEFT);
					this->removeStatus(eStatus::MOVING_RIGHT);
				}
				break;
			}

		case DIK_X:
			{
				if (this->isInStatus(STAND_UP) || this->isInStatus(STAND_DOWN) || this->isInStatus(STAND_DOWN) || this->isInStatus(MOVING_DOWN))
					break;
				if (!this->isInStatus(eStatus::SIT_DOWN) || this->isInStatus(eStatus::MOVING_LEFT) || this->isInStatus(eStatus::MOVING_RIGHT))
					this->jump();
				break;
			}
		case DIK_UP:
			{
				if (_stair != nullptr)
				{
					moveUp();
					_holdingKey = true;
				}
				break;
			}
		case DIK_Z:
			{
				if (this->isInStatus(MOVING_DOWN) || this->isInStatus(MOVING_UP))
				{
					break;
				}
				this->hit();
				break;
			}
		default:
			break;
	}
}

void Player::onKeyReleased(KeyEventArg* key_event)
{
	if (this->isInStatus(eStatus::DIE))
		return;

	switch (key_event->_key)
	{
		case DIK_RIGHT:
			{
				this->removeStatus(eStatus::MOVING_RIGHT);
				break;
			}
		case DIK_LEFT:
			{
				this->removeStatus(eStatus::MOVING_LEFT);
				break;
			}
		case DIK_DOWN:
			{
				this->removeStatus(eStatus::SIT_DOWN);
				if (this->isInStatus(MOVING_DOWN))
				{
					_holdingKey = false;
				}
				break;
			}
		case DIK_UP:
			{
				_holdingKey = false;
				break;
			}
		case DIK_Z:
			{
				break;
			}
		default:
			break;
	}
}

void Player::onCollisionBegin(CollisionEventArg* collision_arg)
{
}

void Player::onCollisionEnd(CollisionEventArg* collision_event)
{
	eID objectID = collision_event->_otherObject->getId();

	switch (objectID)
	{
		case eID::WALL:
			{
				if (preWall == collision_event->_otherObject)
				{
					// hết chạm với land là fall chứ ko có jump
					this->removeStatus(eStatus::JUMPING);
					preWall = nullptr;
				}
				break;
			}


		default:
			break;
	}
}

float Player::checkCollision(BaseObject* object, float dt)
{
	if (object->getStatus() == eStatus::DESTROY || this->isInStatus(eStatus::DIE))
		return 0.0f;
	if (this == object)
		return 0.0f;

	auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
	auto ropeCollisionBody = _rope->getCollisionBody();
	eID objectId = object->getId();
	eDirection direction;

	if (objectId == eID::WALL)
	{
		if (collisionBody->checkCollision(object, direction, dt, false) && !this->isInStatus(MOVING_UP))
		{
			float moveX, moveY;
			if (collisionBody->isColliding(object, moveX, moveY, dt))
			{
				collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
			}


			if (direction == eDirection::TOP && !(this->getVelocity().y > -200 && this->isInStatus(eStatus::JUMPING)))
			{
				auto gravity = (Gravity*)this->_componentList["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);

				this->standing();
				preWall = object;
			}
		}
		else if (preWall == object)
		{
			auto gravity = (Gravity*)this->_componentList["Gravity"];

			if (!this->isInStatus(eStatus::MOVING_DOWN)
				&& !this->isInStatus(eStatus::MOVING_UP)
				&& !this->isInStatus(eStatus::STAND_DOWN)
				&& !this->isInStatus(eStatus::STAND_UP))
			{
				gravity->setStatus(eGravityStatus::FALLING__DOWN);
				if (!this->isInStatus(eStatus::JUMPING) && !this->isInStatus(eStatus::FALLING))
					this->addStatus(eStatus::FALLING);
			}
		}
	}
	else if (objectId == eID::STAIR)
	{
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			_stair = object;
			_directStair = ((Stair*)object)->GetDirection();
		}
		else
		{
			if (_stair == object)
				_stair = nullptr;
		}
	}
	else if (objectId == STAIR_END)
	{
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			_stairEnd = object;
			_directStair = ((StairEnd*)object)->GetDirection();
		}
		else if (_stairEnd == object)
		{
			_stairEnd = nullptr;
		}
	}
	else if (objectId == CANDLE)
	{
		if (_isAttacking)
		{
			if (ropeCollisionBody->checkCollision(object, direction, dt, false))
			{
				object->setStatus(DESTROY);
			}
		}
	}

	return 1.0f;
}

void Player::checkPosition()
{
	if (this->isInStatus(eStatus::DIE))
		return;

	auto viewport = SceneManager::getInstance()->getCurrentScene()->getViewport();
	GVector2 viewport_position = viewport->getPositionWorld();

	if (this->getPositionY() < viewport_position.y - WINDOW_HEIGHT)
	{
		if (_status != eStatus::DIE)
			_status = eStatus::DIE;
		this->die();
	}
}

void Player::standing()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, 0));

	this->removeStatus(eStatus::JUMPING);
	this->removeStatus(eStatus::FALLING);
}


void Player::standingOnStair()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, 0));
	this->removeStatus(eStatus::JUMPING);
	this->removeStatus(eStatus::FALLING);
	this->removeStatus(STAND_UP);
	this->removeStatus(STAND_DOWN);
}

void Player::moveLeft()
{
	if (this->getScale().x > 0)
		this->setScaleX(this->getScale().x * (-1));

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(-_movingSpeed, move->getVelocity().y));
}

void Player::moveRight()
{
	if (this->getScale().x < 0)
		this->setScaleX(this->getScale().x * (-1));

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(_movingSpeed, move->getVelocity().y));
}


void Player::moveDown()
{
	this->removeStatus(MOVING_UP);
	this->removeStatus(STAND_DOWN);
	this->removeStatus(eStatus::STAND_UP);
	this->addStatus(eStatus::MOVING_DOWN);

	auto move = (Movement*)this->_componentList["Movement"];

	if (!_directStair)
	{
		if (this->getScale().x < 0)
			this->setScaleX(this->getScale().x * (-1));
		move->setVelocity(GVector2(_movingSpeed, -_movingSpeed));
	}
	else
	{
		if (this->getScale().x > 0)
			this->setScaleX(this->getScale().x * (-1));
		move->setVelocity(GVector2(-_movingSpeed, -_movingSpeed));
	}

	int x = this->getPositionX() - _stair->getBounding().left;
	int y = this->getPositionY() - _stair->getBounding().bottom;

	x = (x + 9) / 16 * 16;
	y = (y + 9) / 16 * 16;

	if (x == 0 || y == 0)
	{
		this->setStatus(NORMAL);
	}


	if (_stopWatch->isTimeLoop(120))
	{
		if (!_holdingKey)
		{
			move->setVelocity(GVector2(0, 0));

			this->setPositionX(x + _stair->getBounding().left);
			this->setPositionY(x + _stair->getBounding().bottom);

			this->setStatus(STAND_DOWN);
		}

		_stopWatch->restart();
	}
}

void Player::moveDownToStair()
{
	this->setStatus(eStatus::STAND_DOWN);

	if (!_directStair)
	{
		if (this->getScale().x < 0)
			this->setScaleX(this->getScale().x * (-1));
	}
	else
	{
		if (this->getScale().x > 0)
			this->setScaleX(this->getScale().x * (-1));
	}

	this->setPosition(GVector2(_stairEnd->getBounding().left, _stairEnd->getBounding().bottom));
}


void Player::moveUp()
{
	if (this->getStatus() == NORMAL || this->isInStatus(MOVING_LEFT) || this->isInStatus(MOVING_RIGHT) || this->isInStatus(RUNNING))
	{
		if (this->getPositionX() > _stair->getBounding().left + 32)
			return;
		this->setPositionX(_stair->getBounding().left);
	}
	this->setStatus(eStatus::MOVING_UP);

	auto move = (Movement*)this->_componentList["Movement"];


	if (_stair == nullptr)
	{
		this->setStatus(NORMAL);
		_stopWatch->restart();
		return;
	}

	if (_directStair)
	{
		if (this->getScale().x < 0)
			this->setScaleX(this->getScale().x * (-1));
		move->setVelocity(GVector2(_movingSpeed, _movingSpeed));
	}
	else
	{
		if (this->getScale().x > 0)
			this->setScaleX(this->getScale().x * (-1));
		move->setVelocity(GVector2(-_movingSpeed, _movingSpeed));
	}

	if (_stopWatch->isTimeLoop(120))
	{
		if (!_holdingKey)
		{
			move->setVelocity(GVector2(0, 0));

			int x = this->getPositionX() - _stair->getBounding().left;
			int y = this->getPositionY() - _stair->getBounding().bottom;

			x = x / 16 * 16;
			y = y / 16 * 16;

			this->setPositionX(x + _stair->getBounding().left);
			this->setPositionY(x + _stair->getBounding().bottom);

			this->setStatus(STAND_UP);
		}

		_stopWatch->restart();
	}
}

void Player::jump()
{
	if (this->isInStatus(eStatus::JUMPING) || this->isInStatus(eStatus::FALLING))
		return;

	this->addStatus(eStatus::JUMPING);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(move->getVelocity().x, JUMP_VEL));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);

	//SoundManager::getInstance()->Play(eSoundId::JUMP_SOUND);
}

void Player::sitDown()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, move->getVelocity().y));
}

void Player::falling()
{
	auto gravity = (Gravity*)this->_componentList["Gravity"];
	gravity->setStatus(eGravityStatus::FALLING__DOWN);
}

void Player::hit()
{
	_isAttacking = true;
	this->removeStatus(MOVING_LEFT);
	this->removeStatus(MOVING_RIGHT);
	if (this->isInStatus(JUMPING))
		this->addStatus(eStatus::ATTACKING);
	this->addStatus(eStatus::ATTACKING);
	this->_animations[this->getStatus()]->restart();
	this->_rope->restart();
	_ropeStopWatch->restart();
	_ropeStopWatch->isStopWatch(ATTACK_TIME);
}

void Player::revive()
{
}

void Player::die()
{
	if (!this->isInStatus(eStatus::DIE))
		this->setStatus(eStatus::DIE);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(-MOVE_SPEED * (this->getScale().x / SCALE_FACTOR), JUMP_VEL));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);

	//SoundManager::getInstance()->Play(eSoundId::DEAD);
}

void Player::setLifeNumber(int number)
{
}

int Player::getLifeNumber()
{
	return _lifeNum;
}

void Player::setStatus(eStatus status)
{
	_status = status;
}

RECT Player::getBounding()
{
	int offset = 16;

	RECT bound = _sprite->getBounding();

	return bound;
}

GVector2 Player::getVelocity()
{
	auto move = (Movement*)this->_componentList["Movement"];
	return move->getVelocity();
}

void Player::forceMoveRight()
{
	onKeyPressed(new KeyEventArg(DIK_RIGHT));
}

void Player::unforceMoveRight()
{
	onKeyReleased(new KeyEventArg(DIK_RIGHT));
}

void Player::forceMoveLeft()
{
	onKeyPressed(new KeyEventArg(DIK_LEFT));
}

void Player::unforceMoveLeft()
{
	onKeyReleased(new KeyEventArg(DIK_LEFT));
}

void Player::forceJump()
{
	onKeyPressed(new KeyEventArg(DIK_X));
}

void Player::unforceJump()
{
	onKeyReleased(new KeyEventArg(DIK_X));
}

void Player::removeGravity()
{
	auto graivity = (Gravity*)(this->_componentList.find("Gravity")->second);
	graivity->setGravity(VECTOR2ZERO);
}

void Player::unhookinputevent()
{
	if (_input != nullptr)
		__unhook(_input);
}

float Player::getMovingSpeed()
{
	return _movingSpeed;
}

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt)
{
	if (activeobj != nullptr && passiveobj != nullptr)
	{
		activeobj->checkCollision(passiveobj, dt);
	}
}

eID Player::getStage()
{
	return _currentStage;
}

void Player::setStage(eID id)
{
	_currentStage = id;
}
