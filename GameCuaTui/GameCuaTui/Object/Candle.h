#ifndef _CANDLE_H
#define _CANDLE_H

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"

class Candle : public BaseObject
{
public:
	Candle(int x, int y);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
};
#endif