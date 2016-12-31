#ifndef _MONEY_H_
#define _MONEY_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"

class Money : public BaseObject
{
public:
	Money(int x, int y, int type = 0);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	float checkCollision(BaseObject* object, float dt) override;

	int GetCoin();
protected:
	map<string, IComponent*> _componentList;
	bool _stop;
	int _type;

	StopWatch* _destroyStopWatch;
	bool _startDestroyStopWatch;
};
#endif