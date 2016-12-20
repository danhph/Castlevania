#ifndef _ROPE_H_
#define _ROPE_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"

class Rope : public BaseObject
{
public:
	Rope(int x, int y);


	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void updateRopePos(GVector2 pos);

	void restart();

	RECT getBounding() override;
	
	void upgradeRope();
	void resetRope();

	float checkCollision(BaseObject* object, float dt);

	CollisionBody* getCollisionBody();

protected:
	void setRope(int id);
	map<int,Animation*> _animations;
	map<string, IComponent*> _componentList;
	int _currentRope;
};
#endif