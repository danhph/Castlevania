#include "Player.h"
#include "../Framework/SceneManager.h"

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
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::PLAYER, "walk_left_01"));
	_sprite->setZIndex(1.0f);

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);

	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);

	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Player::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Player::onCollisionEnd);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::PLAYER, "walk_left_01", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.12f);
	_animations[eStatus::RUNNING]->addFrameRect(eID::PLAYER, "walk_left_01", "walk_left_02", "walk_left_03", NULL);

	this->setOrigin(GVector2(0.5f, 0.0f));
	this->setStatus(eStatus::NORMAL);

	// create stopWatch
	_stopWatch = new StopWatch();

	this->resetValues();

	_info = new Info(GVector2(350, 40), this->getLifeNumber());
	_info->init();
}

void Player::update(float deltatime)
{
	this->checkPosition();

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
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex | eStatus::RUNNING);
	}

	if ((_currentAnimateIndex & eStatus::JUMPING) == eStatus::JUMPING)
	{
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

	_preObject = nullptr;

	_movingSpeed = MOVE_SPEED;

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void Player::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations[_currentAnimateIndex]->draw(spriteHandle, viewport);

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
}

void Player::onKeyReleased(KeyEventArg* key_event)
{
}

void Player::onCollisionBegin(CollisionEventArg* collision_arg)
{
}

void Player::onCollisionEnd(CollisionEventArg* collision_event)
{
}

float Player::checkCollision(BaseObject* object, float dt)
{
	if (object->getStatus() == eStatus::DESTROY || this->isInStatus(eStatus::DIE))
		return 0.0f;
	if (this == object)
		return 0.0f;

	auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
	eID objectId = object->getId();
	eDirection direction;

	if (objectId == eID::WALL)
	{
		if (!this->isInStatus(eStatus(eStatus::JUMPING | eStatus::FALLING)) && collisionBody->checkCollision(object, direction, dt, false));
	}
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

void Player::moveLeft()
{
	auto viewport = SceneManager::getInstance()->getCurrentScene()->getViewport();
	GVector2 viewportPosition = viewport->getPositionWorld();
	float playerPositionX = this->getPositionX();
	auto halfwidth = this->getSprite()->getFrameWidth() * this->getSprite()->getOrigin().x;
	// Không cho đi vượt cạnh trái
	if (playerPositionX + halfwidth - _movingSpeed * 0.33 <= viewportPosition.x)
	{
		this->setPositionX(viewportPosition.x + halfwidth);
		return;
	}
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
}

RECT Player::getBounding()
{
	int offset = 10;

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
