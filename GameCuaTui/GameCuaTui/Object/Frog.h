#ifndef _FROG_H
#define _FROG_H

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>
#include "BigHeart.h"
#include "Heart.h"

#define FROG_MOVE_SPEED 70

class Frog : public BaseObject
{
public:
	Frog(int x, int y);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void wasHit();

	bool isDead();


	void MoveToPlayer(GVector2 pos);
protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;

	bool _isDead;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	int _initX;

};
#endif