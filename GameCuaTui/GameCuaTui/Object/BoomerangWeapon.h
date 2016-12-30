#ifndef _BOOMERANG_WEAPON_H_
#define _BOOMERANG_WEAPON_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../FrameWork/Animation.h"
#include "../Framework/StopWatch.h"
#include "DaggerWeapon.h"

#define FLYING_SPEED 250

class BoomerangWeapon : public Weapon
{
public:
	BoomerangWeapon(int x, int y, bool direct);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	CollisionBody* getCollisionBody() override;

	bool IsBoomerangComeBack();
	void ComeBack();
protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
	bool _comeBack;
};
#endif