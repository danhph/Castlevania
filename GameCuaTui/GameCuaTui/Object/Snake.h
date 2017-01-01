#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"

#define SNAKE_MOVE_SPEED 125

class Snake : public BaseObject
{
public:
	Snake(int x, int y, bool direct);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	float checkCollision(BaseObject* object, float dt) override;

	bool checkWasHit();

	void wasHit();
protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
	int _initX;
	bool _wasHit;
	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _stopwatch;
	bool _direct;
};
#endif