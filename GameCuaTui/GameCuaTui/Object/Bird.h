#ifndef _BIRD_H
#define _BIRD_H

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

#define BIRD_MOVE_SPEED 125

class Bird : public BaseObject
{
public:
	Bird(int x, int y, bool direct);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void wasHit();
	bool isDead();	
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