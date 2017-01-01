#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"

#define DELAY_SHOW 3000

class Treasure : public BaseObject
{
public:
	Treasure(int x, int y, int initX, int initY);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void Active(bool active);
	bool IsActive();
protected:
	int _initX;
	int _initY;
	bool _active;

	Animation* _animation;

	StopWatch* _stopWatch;

	StopWatch* _destroyStopWatch;
	bool _startDestroyStopWatch;

	map<string, IComponent*> _componentList;
};
#endif