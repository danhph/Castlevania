#ifndef _INCREASE_H_
#define _INCREASE_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"

class IncreaseWeapon : public BaseObject
{
public:
	IncreaseWeapon(int x, int y);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	float checkCollision(BaseObject* object, float dt) override;

	void setNum(int num);
protected:
	map<string, IComponent*> _componentList;
	bool _stop;
	int _initX;

	StopWatch* _destroyStopWatch;
	bool _startDestroyStopWatch;

};
#endif