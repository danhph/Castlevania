#ifndef _DOOR_H
#define _DOOR_H

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"

class Door : public BaseObject
{
public:
	Door(int x, int y);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	void Open();

protected:
	
	Animation* _animation;
	Animation* _closeAnimation;
	StopWatch* _stopwatch;
	
	bool _wasOpen;
	bool _isClosing;
	map<string, IComponent*> _componentList;
};
#endif