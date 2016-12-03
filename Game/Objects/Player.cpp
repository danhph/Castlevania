#include "Player.h"

Player::Player(int life) : BaseObject(eID::PLAYER)
{
	_canJumpDown = true;
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
	_shootAnimateStopWatch = new StopWatch();
	_shootStopWatch = new StopWatch();

	_isHolding = false;

	_currentAnimateIndex = eStatus::NORMAL; // debug

	this->resetValues();
	
	_info = new Info(GVector2(350, 40), this->getLifeNumber());
	_info->init();
}

void Player::update(float deltatime)
{
	// đang protect thì đếm xuống
	if (_protectTime > 0)
	{
		_protectTime -= deltatime;
	}

	this->checkPosition();

	this->updateStatus(deltatime);

	this->updateCurrentAnimateIndex();

	_animations[_currentAnimateIndex]->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Player::resetValues()
{
}

void Player::updateInput(float dt)
{
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
	SAFE_DELETE(_shootStopWatch);
	SAFE_DELETE(_shootAnimateStopWatch);
	SAFE_DELETE(_reviveStopWatch);
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
	return 0.0f;
}

void Player::checkPosition()
{
}

void Player::standing()
{
}

void Player::moveLeft()
{
}

void Player::moveRight()
{
}

void Player::jump()
{
}

void Player::layDown()
{
}

void Player::falling()
{
}

void Player::shoot()
{
}

void Player::revive()
{
}

void Player::die()
{
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

void Player::updateStatus(float dt)
{
}

void Player::updateCurrentAnimateIndex()
{
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
