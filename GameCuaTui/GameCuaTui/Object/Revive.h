#ifndef __REVIVE_H__
#define __REVIVE_H__

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"

class Revive : public BaseObject
{
public:
	Revive(int x, int y, int width, int height);
	~Revive();

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	GVector2 getPosition() override;
private:
	map<string, IComponent*> _listComponent;

	RECT _bound;

	eID _nextStage;
};


#endif // !__REVIVE_H__
