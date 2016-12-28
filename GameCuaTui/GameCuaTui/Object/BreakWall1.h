#ifndef _BREAKWALL1_H_
#define _BREAKWALL1_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "QuadtreeNode.h"

class BreakWall1 : public BaseObject
{
public:
	BreakWall1(int x, int y);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	bool isBroken();

	void wasHit();

protected:
	map<string, IComponent*> _componentList;
	bool _wasHit;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;
};
#endif