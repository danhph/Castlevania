#ifndef _CANDLE_H
#define _CANDLE_H

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "Heart.h"
#include "BigHeart.h"
#include "QuadtreeNode.h"
#include "Money.h"
#include "RopeUpgrade.h"
#include "Dagger.h"
#include "Boomerang.h"
#include "Axe.h"
#include "Potion.h"
#include "Cross.h"
#include <ctime>
class Candle : public BaseObject
{
public:
	Candle(int x, int y, eID item = ITEM);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	bool checkWasHit();

	void wasHit();

protected:
	bool _wasHit;
	Animation* _animation;
	Sprite* _effect;
	Animation* _effectAnimation;

	StopWatch* _stopwatch;

	map<string, IComponent*> _componentList;

	eID _item;
};
#endif