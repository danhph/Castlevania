#ifndef _BLUEBAT_H
#define _BLUEBAT_H

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

#define BAT_MOVE_SPEED 120

class BlueBat : public BaseObject
{
public:
	BlueBat(int x, int y);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	
	void wasHit();
	bool isDead();

	void Active(bool direct);
	bool isActive();

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
	float _initX;
	bool _isDead;

	bool _isActive;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;
};
#endif