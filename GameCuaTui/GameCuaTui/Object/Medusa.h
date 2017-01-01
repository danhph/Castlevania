#ifndef _MEDUSA_H_
#define _MEDUSA_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "QuadtreeNode.h"
#include "Ball.h"
#include "Snake.h"
#include "../Framework/SceneManager.h"

#define MEDUSA_MOVE_SPEED 60
#define MEDUSA_SNAKE_DELAY 4000
#define MEDUSA_INIT_DELAY 5000
#define MEDUSA_MOVE_DELAY 1500
#define MEDUSA_AMPLITUDE GVector2(0, 40)

class Medusa : public BaseObject
{
public:
	Medusa(int x, int y, int checkPoint, eID next);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void wasHit();
	bool isDead();
	int GetHitPoint();

	void Active();
	bool isActive();

	int getCheckPoint();

	void SetDirect(bool direct);
	bool GetDirect();

	void DelayMove();
	bool IsDelayMove();

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
	
	float _initX;
	float _initY;
	
	bool _isDelayMove;
	bool _isActive;
	StopWatch* _stopStopWatch;

	bool _isDead;
	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	int _checkPoint;

	bool _playerDirect;
	StopWatch* _initSnakeStopWatch;

	int _hitpoint;

	StopWatch* _hitStopWatch;
	bool _startHit;

	eID _next;
};
#endif