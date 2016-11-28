﻿/*
update 22/11/2015
by Luu The Vinh

- Cập nhật xét ca chạm với Land, Water
- Chuyển động nhân vật

update 30/11/2015
- Hiệu ứng nhảy xuông nước
*/

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

#define BILL_MOVE_SPEED 125
#define BILL_JUMP_VEL 450
#define GRAVITY 800
#define SHOOT_SPEED 200.0f
#define MAX_BULLET 4
#define REVIVE_TIME 2000
#define PROTECT_TIME 3000

class BaseObject;

[event_receiver(native)]
class Bill : public BaseObject, public IControlable
{
public:
	Bill(int life = 3);
	~Bill();

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

	// Đổi kiểu đạn. 
	void changeBulletType(eAirCraftType);

	void setLifeNumber(int number);
	int getLifeNumber();

	void setShootSpeed(float speed);
	float getShootSpeed();

	void setMaxBullet(int number);
	int getMaxBullet();

	void setStatus(eStatus status) override;

	void removeGravity();
	void forceMoveRight();
	void unforceMoveRight();
	void forceMoveLeft();
	void unforceMoveLeft();
	void forceJump();
	void unforceJump();
	void unhookinputevent();
	// Character action.
	void standing();
	void moveLeft();
	void moveRight();
	void jump();
	void layDown();
	void falling();
	void shoot();
	void revive();
	void die();
	void swimming();

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

	list<Bullet* > _listBullets;

	// Dùng để tạo ra đạn, nếu ăn máy bay tiếp đạn thì thay đổi thông số này, nếu bắn đạn thì dựa trên thuộc tính này để chọn loại đạn khởi tạo
	eBulletType _currentGun;

	int _lifeNum;
	float _shootSpeed;
	int _maxBullet;
	float _protectTime;

	// ăn đạn B bảo vệ chạm mấy thằng lính sẽ giết đc nó
	bool _touchKill;

	LifeUI* _lifeUI;

	GVector2 getVelocity();

	void updateStatus(float dt);

	void updateCurrentAnimateIndex();

	eDirection getAimingDirection();

	Bullet* getBulletFromGun(GVector2 position, float angle);

	// Tung Ho: kiểm tra và xoá đạn hết hiệu lực.
	void deleteBullet();

	// reset các thuộc tính lại giá trị ban đầu.
	void resetValues();

	BaseObject* _preObject;
	bool _isHolding;
};

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt);


#endif // !__BILL_H__
