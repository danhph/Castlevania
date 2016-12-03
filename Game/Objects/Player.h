#ifndef __BILL_H__
#define __BILL_H__

#include "../FrameWork/define.h"
#include "../FrameWork/Animation.h"
#include "../FrameWork/InputController.h"
#include "../Framework/Viewport.h"
#include "../FrameWork/StopWatch.h"
#include "BaseObject.h"
#include "../Framework/IComponent.h"
#include "CollisionBody.h"

#include <list>
#include "Info.h"

#define MOVE_SPEED 125
#define JUMP_VEL 450
#define GRAVITY 800
#define REVIVE_TIME 2000
#define PROTECT_TIME 3000

class BaseObject;

EVENT_RECEIVER
class Player : public BaseObject, public IControlable
{
public:
	Player(int life = 3);
	~Player();

	void init();
	void updateInput(float dt);
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	void onKeyPressed(KeyEventArg* key_event);
	void onKeyReleased(KeyEventArg* key_event);

	void onCollisionBegin(CollisionEventArg* collision_arg);
	void onCollisionEnd(CollisionEventArg* collision_arg);

	float checkCollision(BaseObject* object, float dt);
	void checkPosition();


	void setLifeNumber(int number);
	int getLifeNumber();

	void setStatus(eStatus status) override;

	void removeGravity();
	void forceMoveRight();
	void unforceMoveRight();
	void forceMoveLeft();
	void unforceMoveLeft();
	void forceJump();
	void unforceJump();
	void unhookinputevent();

	void standing();
	void moveLeft();
	void moveRight();
	void jump();
	void layDown();
	void falling();
	void shoot();
	void revive();
	void die();

	float getMovingSpeed();

	RECT getBounding() override;

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	float _movingSpeed;
	StopWatch* _stopWatch;
	StopWatch* _shootStopWatch;
	StopWatch* _shootAnimateStopWatch;
	StopWatch* _reviveStopWatch;

	bool _canJumpDown;
	eStatus _currentAnimateIndex;

	int _lifeNum;
	float _protectTime;

	Info* _info;

	GVector2 getVelocity();

	void updateStatus(float dt);

	void updateCurrentAnimateIndex();

	void resetValues();

	BaseObject* _preObject;
	bool _isHolding;
};

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt);

#endif // !__BILL_H__
