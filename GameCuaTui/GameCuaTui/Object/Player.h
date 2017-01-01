#ifndef _PLAYER_H_
#define _PLAYER_H_

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
#include "Heart.h"
#include "BigHeart.h"
#include "../Framework/SceneManager.h"
#include "Stair.h"
#include "StairEnd.h"
#include "MovingStair.h"
#include "Candle.h"
#include "End.h"
#include "Door.h"
#include "Back.h"
#include "Soldier.h"
#include "BlueBat.h"
#include "Dinosaur.h"
#include "Fireball.h"
#include "BreakWall.h"
#include "BreakWall1.h"
#include "DaggerWeapon.h"
#include "BoomerangWeapon.h"
#include "BirdRange.h"
#include "FrogRange.h"
#include "AxeWeapon.h"
#include "Money.h"
#include "IncreaseWeapon.h"
#include "Medusa.h"
#include "Crown.h"
#include "Treasure.h"
#include "../Framework/StageManager.h"
#include "../Framework/SoundManager.h"
#include <thread>

#define MOVE_SPEED 125
#define JUMP_VEL 350

#define GRAVITY 800
#define ATTACK_TIME 600
#define PROTECT_TIME 2000

EVENT_RECEIVER
class Player : public BaseObject, public IControlable
{
public:
	Player();
	~Player();

	void init();
	void updateInput(float dt);
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	void onKeyPressed(KeyEventArg* key_event);
	void onKeyReleased(KeyEventArg* key_event);

	float checkCollision(BaseObject* object, float dt);
	void checkPosition();

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

	void behit(eDirection direct);

	void sitDown();
	void falling();
	void hit();
	void revive();
	void die();

	float getMovingSpeed();

	void setStage(eID id);
	eID getStage();
	
	bool isChangedStage();

	RECT getBounding() override;
	void resetValues();

	GVector2 getPosition() override;

	bool IsPlayingMove();
	void StartMovieMove();
	void StopMovie();

	void UseCross();
	bool GetCross();

	eDirection getMapDirection();

	bool EndLevel();

	Info* GetInfo();
private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	float _movingSpeed;
	StopWatch* _stairStopWatch;

	eStatus _currentAnimateIndex;

	Info* _info;

	GVector2 getVelocity();

	void updateStatus(float dt);
	void updateAttackStatus(float dt);
	void updateCurrentAnimateIndex();
	bool weaponCheckCollision(BaseObject* object, eDirection & direction, float dt, bool updatePosition);

	BaseObject* preWall;

	BaseObject* _stair;
	bool _directStair;
	bool _holdingKey;

	bool _isAttacking;
	bool _isRope;
	StopWatch* _attackStopWatch;
	StopWatch* _weaponStopWatch;
	
	vector<Weapon*> _listWeapon;

	BaseObject* _stairEnd;
	GVector2 _backPos;
	eStatus _backStatus;
	bool _isBack;

	eID _currentStage;
	bool _isChangedStage;

	Rope* _rope;

	float _protectTime;

	eID _reviveStage;
	GVector2 _revivePos;
	bool _isRevive;
	
	bool _isPlayingMovie;
	bool _movieStartMove;
	eDirection _mapDirect;

	int _endMoviePosX;

	bool _cross;

	bool _endLevel;
};

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt);

#endif // !_PLAYER_H_
