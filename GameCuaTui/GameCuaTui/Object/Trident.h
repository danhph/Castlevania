#ifndef _TRIDENT_H_
#define _TRIDENT_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "Heart.h"
#include "BigHeart.h"
#include "QuadtreeNode.h"
#include <ctime>
class Trident : public BaseObject
{
public:
	Trident(int x, int y, bool full = true);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	
	RECT getBounding() override;
protected:
	Animation* _animation;
	bool _full;
	map<string, IComponent*> _componentList;
};
#endif