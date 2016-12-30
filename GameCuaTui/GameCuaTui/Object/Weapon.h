#ifndef WEAPON_H_
#define _WEAPON_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "CollisionBody.h"


class Weapon : public BaseObject
{
public:
	Weapon(eID);
	virtual CollisionBody* getCollisionBody();	
};
#endif