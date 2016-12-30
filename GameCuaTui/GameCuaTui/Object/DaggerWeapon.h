#ifndef _DAGGER_WEAPON_H_
#define _DAGGER_WEAPON_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "Weapon.h"

#define FLYING_SPEED 250

class DaggerWeapon : public Weapon
{
public:
	DaggerWeapon(int x, int y, bool direct);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	CollisionBody* getCollisionBody() override;
protected:
	map<string, IComponent*> _componentList;
};
#endif