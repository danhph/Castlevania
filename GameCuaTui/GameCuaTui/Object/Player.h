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
#include "Rope.h"

#define MOVE_SPEED 125
#define JUMP_VEL 350

#define GRAVITY 800
#define ATTACK_TIME 600
#define PROTECT_TIME 3000

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
	void standingOnStair();
	void moveLeft();
	void moveRight();
	
	void moveUp();
	void moveDown();
	void moveDownToStair();

	void jump();
	void sitDown();
	void falling();
	void hit();
	void revive();
	void die();

	float getMovingSpeed();

	void setStage(eID id);
	eID getStage();

	RECT getBounding() override;
	void resetValues();

	GVector2 getPosition() override;

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	float _movingSpeed;
	StopWatch* _stopWatch;
	StopWatch* _ropeStopWatch;

	eStatus _currentAnimateIndex;

	int _lifeNum;

	Info* _info;

	GVector2 getVelocity();

	void updateStatus(float dt);

	void updateCurrentAnimateIndex();

	BaseObject* preWall;

	BaseObject* _stair;
	bool _directStair;
	bool _holdingKey;

	bool _isAttacking;

	BaseObject* _stairEnd;

	eID _currentStage;

	Rope* _rope;
};

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt);

#endif // !__BILL_H__
