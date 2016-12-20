#ifndef _SOLDIER_H
#define _SOLDIER_H

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"

class Soldier : public BaseObject
{
public:
	Soldier(int x, int y, int activeX);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
	int _activeXLeft;
	int _activeXRight;
};
#endif