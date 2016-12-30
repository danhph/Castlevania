<<<<<<< HEAD
#ifndef _TRIDENT_H_
#define _TRIDENT_H_
=======
#ifndef _TRIDENT_H
#define _TRIDENT_H
>>>>>>> a37675e304b9028bd7ad4f09e440faed3da0faef

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
<<<<<<< HEAD
#include "Heart.h"
#include "BigHeart.h"
#include "QuadtreeNode.h"
#include <ctime>
class Trident : public BaseObject
{
public:
	Trident(int x, int y, bool full = true);
=======
#include "QuadtreeNode.h"
#include <ctime>
#include "BigHeart.h"
#include "Heart.h"

#define TRIDENT_MOVE_SPEED 70

class Trident : public BaseObject
{
public:
	Trident(int x, int y, int activeX);
>>>>>>> a37675e304b9028bd7ad4f09e440faed3da0faef


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
<<<<<<< HEAD
	
	RECT getBounding() override;
protected:
	Animation* _animation;
	bool _full;
	map<string, IComponent*> _componentList;
=======

	void wasHit(int hitpoint);

	bool isDead();

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
	int _activeXLeft;
	int _activeXRight;

	int _hitPoint;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHit;

>>>>>>> a37675e304b9028bd7ad4f09e440faed3da0faef
};
#endif